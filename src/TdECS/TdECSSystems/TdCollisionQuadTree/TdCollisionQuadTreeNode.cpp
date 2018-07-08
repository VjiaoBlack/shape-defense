/**
 * TdCollisionQuadTreeNode.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdCollisionQuadTreeNode.hpp"
#include <TdGame.hpp>
#include "../../TdECSEntity.hpp"

TdCollisionQuadTreeNode *TdCollisionQuadTreeNode::getContainingNode(
    TdGame *game, TdECSSystem *system, int entID) {
  auto ent = system->m_entities[entID].get();
  if (m_tl) {
    if (m_tl->m_rect.contains(ent)) {
      return m_tl->getContainingNode(game, system, entID);
    }
    if (m_tr->m_rect.contains(ent)) {
      return m_tr->getContainingNode(game, system, entID);
    }
    if (m_bl->m_rect.contains(ent)) {
      return m_bl->getContainingNode(game, system, entID);
    }
    if (m_br->m_rect.contains(ent)) {
      return m_br->getContainingNode(game, system, entID);
    }
  }
  if (m_rect.contains(system->m_entities[entID].get())) {
    return this;
  } else {
    return nullptr;
  }
}

bool TdCollisionQuadTreeNode::tryAddEntID(TdGame *game, TdECSSystem *system,
                                          int entID) {
  auto node = getContainingNode(game, system, entID);

  if (node) {
    node->m_entIDs.insert(entID);
    return true;
  } else {
    return false;
  }
}

void TdCollisionQuadTreeNode::removeEntID(TdGame *game, TdECSSystem *system,
                                          int entID) {
  auto node = getContainingNode(game, system, entID);
  if (!node) {
    std::cerr
        << "ERROR: collision quad tree attempted to remove nonexistent node."
        << std::endl;
    double a;
    //    exit(2);
    return;
  }

  if (node->m_entIDs.count(entID) == 0) {
    std::cerr
        << "ERROR: collision quad tree attempted to remove nonexistent node."
        << std::endl;
    double a;
    //    exit(1);
    return;
  }

  node->m_entIDs.erase(entID);
}

bool TdCollisionQuadTreeNode::containsEntID(TdGame *game, TdECSSystem *system,
                                            int entID) {
  if (m_tl) {
    bool ans = false;
    ans = ans || m_tl->containsEntID(game, system, entID);
    ans = ans || m_tr->containsEntID(game, system, entID);
    ans = ans || m_bl->containsEntID(game, system, entID);
    ans = ans || m_br->containsEntID(game, system, entID);
    return ans;
  } else {
    return m_entIDs.count(entID);
  }
}

void TdCollisionQuadTreeNode::refreshNode(TdGame *game, TdECSSystem *system,
                                          std::set<int> &outside) {
  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0x80, 0x80, 0xFF, 0xFF);
  SDL_Rect draw{(int)m_rect.pos.x, (int)m_rect.pos.y, (int)m_rect.w,
                (int)m_rect.h};
  SDL_RenderDrawRect(game->m_SDLRenderer, &draw);

  // collect entIDs that don't belong
  if (m_tl) {
    m_tl->refreshNode(game, system, outside);

    // refreshNode might delete some nodes...
    // so we must re-check to see if child nodes are null.
    if (m_tr) m_tr->refreshNode(game, system, outside);
    if (m_bl) m_bl->refreshNode(game, system, outside);
    if (m_br) m_br->refreshNode(game, system, outside);
  } else {
    if (m_entIDs.size() > 8) {
      TdECSRect newBaseRect = m_rect;
      newBaseRect.w /= 2.0;
      newBaseRect.h /= 2.0;

      TdECSRect rectTL = newBaseRect;
      TdECSRect rectTR = newBaseRect;
      TdECSRect rectBL = newBaseRect;
      TdECSRect rectBR = newBaseRect;

      rectTR.pos.x += m_rect.w / 2.0;
      rectBL.pos.y += m_rect.h / 2.0;
      rectBR.pos.x += m_rect.w / 2.0;
      rectBR.pos.y += m_rect.h / 2.0;

      this->m_tl =
          std::move(std::make_unique<TdCollisionQuadTreeNode>(this, rectTL));
      this->m_tr =
          std::move(std::make_unique<TdCollisionQuadTreeNode>(this, rectTR));
      this->m_bl =
          std::move(std::make_unique<TdCollisionQuadTreeNode>(this, rectBL));
      this->m_br =
          std::move(std::make_unique<TdCollisionQuadTreeNode>(this, rectBR));

      if (m_parent) {
        for (auto it = m_entIDs.begin(); it != m_entIDs.end(); it++) {
          outside.insert(*it);
        }
        m_entIDs.clear();
      }
    }
  }

    // put non-fitting objects upwards
    if (m_parent) {
      for (auto it = m_entIDs.begin(); it != m_entIDs.end();) {
        if (system->m_entities.count(*it) == 0 ||
            system->m_entities[*it]->m_dead) {
          it = m_entIDs.erase(it);
        } else if (!this->m_rect.contains(system->m_entities[*it].get())) {
          outside.insert(*it);
          it = m_entIDs.erase(it);
        } else {
          it++;
        }
      }
    }


  // attempt to redistribute entIDs
  if (m_parent) {
    for (auto it = outside.begin(); it != outside.end();) {
      // if entID is inside, put into m_entIDs
      if (this->tryAddEntID(game, system, *it)) {
        it = outside.erase(it);
      } else {
        it++;
      }
    }
  }

  if (m_entIDs.size() == 0) {
    if (this->m_parent && this->m_parent->m_entIDs.size() == 0 &&
        this->m_parent->m_tl && this->m_parent->m_tl->m_tl == nullptr &&
        this->m_parent->m_tr->m_tl == nullptr &&
        this->m_parent->m_bl->m_tl == nullptr &&
        this->m_parent->m_br->m_tl == nullptr &&
        this->m_parent->m_tl->m_entIDs.size() == 0 &&
        this->m_parent->m_tr->m_entIDs.size() == 0 &&
        this->m_parent->m_bl->m_entIDs.size() == 0 &&
        this->m_parent->m_br->m_entIDs.size() == 0) {
      // if this is a leaf and its parent and siblings have 0 entIDs,
      // delete this and its siblings
      m_parent->m_tl.reset(nullptr);
      m_parent->m_tr.reset(nullptr);
      m_parent->m_bl.reset(nullptr);
      m_parent->m_br.reset(nullptr);
    }
  }
}

void TdCollisionQuadTreeNode::getAllWithinRadius(TdGame *game,
                                                 TdECSSystem *system,
                                                 std::set<int> &ents, double x,
                                                 double y, double r) {
  for (auto entID : m_entIDs) {
    double entX, entY;
    std::tie(entX, entY) = getPosition(system->m_entities[entID].get());

    double dist = std::sqrt((x - entX) * (x - entX) + (y - entY) * (y - entY));

    if (dist <= r) {
      ents.insert(entID);
    }
  }

  if (m_tl) {
    m_tl->getAllWithinRadius(game, system, ents, x, y, r);
    m_tr->getAllWithinRadius(game, system, ents, x, y, r);
    m_bl->getAllWithinRadius(game, system, ents, x, y, r);
    m_br->getAllWithinRadius(game, system, ents, x, y, r);
  }
}

int TdCollisionQuadTreeNode::getNumEnts() {
  int num = m_entIDs.size();
  if (m_tl) {
    num += m_tl->getNumEnts();
    num += m_tr->getNumEnts();
    num += m_bl->getNumEnts();
    num += m_br->getNumEnts();
  }
  return num;
}

int TdCollisionQuadTreeNode::getDeepestLayer(int start) {
  if (!m_tl) {
    return start;
  } else {
    int ans = start + 1;
    int test = 0;
    if ((test = m_tl->getDeepestLayer(start + 1)) > ans) {
      ans = test;
    }
    if ((test = m_tr->getDeepestLayer(start + 1)) > ans) {
      ans = test;
    }
    if ((test = m_bl->getDeepestLayer(start + 1)) > ans) {
      ans = test;
    }
    if ((test = m_br->getDeepestLayer(start + 1)) > ans) {
      ans = test;
    }

    return ans;
  }
}
