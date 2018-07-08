/**
 * TdCollisionQuadTreeNode.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdCollisionQuadTreeNode.hpp"
#include <TdECS/TdECSSystems/TdECSSystemPosUtils.hpp>
#include <TdGame.hpp>
#include <csignal>
#include "../../TdECSEntity.hpp"

void TdCollisionQuadTreeNode::getAdjacentNodes(
    list<TdCollisionQuadTreeNode *> &nodes) {
  nodes.push_back(this);

  if (!m_parent) {
    return;
  }

  nodes.push_back(m_parent);

  if (!m_parent->m_parent) {
    return;
  }

  nodes.push_back(m_parent->m_parent);
}

TdCollisionQuadTreeNode *TdCollisionQuadTreeNode::getContainingNode(
    TdECSSystem *system, int entID) {
  //  printf("  node pos: %d, %d : %d, %d\n", (int)m_rect.pos.x,
  //  (int)m_rect.pos.y,
  //         (int)m_rect.w, (int)m_rect.h);

  auto ent = system->getEnt(entID);
  if (m_tl) {
    if (m_tl->m_rect.contains(ent)) {
      return m_tl->getContainingNode(system, entID);
    }
    if (m_tr->m_rect.contains(ent)) {
      return m_tr->getContainingNode(system, entID);
    }
    if (m_bl->m_rect.contains(ent)) {
      return m_bl->getContainingNode(system, entID);
    }
    if (m_br->m_rect.contains(ent)) {
      return m_br->getContainingNode(system, entID);
    }
  }
  if (m_rect.contains(system->getEnt(entID))) {
    //    printf("  RECT CONTAINS\n");
    return this;
  } else {
    //    printf("  RECT CANT CONTAIN\n");
    return nullptr;
  }
}

TdCollisionQuadTreeNode *TdCollisionQuadTreeNode::forceSearch(
    TdECSSystem *system, int entID) {
  if (m_ents.count(entID)) {
    return this;
  }

  if (m_tl) {
    if (m_tl->m_ents.count(entID)) {
      return m_tl.get();
    } else {
      m_tl->forceSearch(system, entID);
    }
    if (m_tr->m_ents.count(entID)) {
      return m_tr.get();
    } else {
      m_tr->forceSearch(system, entID);
    }
    if (m_bl->m_ents.count(entID)) {
      return m_bl.get();
    } else {
      m_bl->forceSearch(system, entID);
    }
    if (m_br->m_ents.count(entID)) {
      return m_br.get();
    } else {
      m_br->forceSearch(system, entID);
    }
  }

  return nullptr;
}

bool TdCollisionQuadTreeNode::tryAddEntID(TdECSSystem *system, int entID,
                                          TdECSEntity *ent) {
  auto node = getContainingNode(system, entID);

  if (node) {
    node->m_ents[entID] = ent;
    return true;
  } else {
    return false;
  }
}

void TdCollisionQuadTreeNode::removeEntID(TdECSSystem *system, int entID) {
  auto node = getContainingNode(system, entID);
  if (!node) {
    std::cerr << "ERROR: collision quad tree attempted to remove from "
                 "nonexistent node."
              << std::endl;
    raise(SIGSEGV);
    //    exit(2);
    return;
  }

  if (node->m_ents.count(entID) == 0) {
    std::cerr << "ERROR: collision quad tree attempted to remove ent from "
                 "incorrect node."
              << std::endl;

    // where the hell is it then???

    //    auto node =
    //        system->m_collisions.m_qtree->m_root->forceSearch(game, system,
    //        entID);

    //    printf("  FOUND %d, %d: %d, %d\n", (int)node->m_rect.pos.x,
    //           (int)node->m_rect.pos.y, (int)node->m_rect.w,
    //           (int)node->m_rect.h);

    raise(SIGSEGV);
    //        exit(1);
    return;
  }

  node->m_ents.erase(entID);
}

bool TdCollisionQuadTreeNode::containsEntID(TdECSSystem *system, int entID) {
  if (m_tl) {
    bool ans = false;
    ans = ans || m_tl->containsEntID(system, entID);
    ans = ans || m_tr->containsEntID(system, entID);
    ans = ans || m_bl->containsEntID(system, entID);
    ans = ans || m_br->containsEntID(system, entID);
    return ans;
  } else {
    return m_ents.count(entID);
  }
}

void TdCollisionQuadTreeNode::refreshNode(
    TdGame *game, TdECSSystem *system,
    std::unordered_map<int, TdECSEntity *> &outside) {
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
    if (m_ents.size() > 4) {
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
        for (auto it = m_ents.begin(); it != m_ents.end(); it++) {
          outside.insert(*it);
        }
        m_ents.clear();
      }
    }
  }

  // put non-fitting objects upwards
  if (m_parent) {
    for (auto it = m_ents.begin(); it != m_ents.end();) {
      if (!this->m_rect.contains(it->second)) {
        outside.insert(*it);
        it = m_ents.erase(it);
      } else {
        it++;
      }
    }
  }

  // attempt to redistribute entIDs
  if (m_parent) {
    for (auto it = outside.begin(); it != outside.end();) {
      // if entID is inside, put into m_ents
      if (this->tryAddEntID(system, it->first, it->second)) {
        it = outside.erase(it);
      } else {
        it++;
      }
    }
  }

  // attempt to redistribute entIDs DOWN
  if (m_tl) {
    for (auto it = m_ents.begin(); it != m_ents.end();) {
      // if entID is inside, put into m_ents
      if (m_tl->tryAddEntID(system, it->first, it->second)) {
        it = m_ents.erase(it);
      } else if (m_tr->tryAddEntID(system, it->first, it->second)) {
        it = m_ents.erase(it);
      } else if (m_bl->tryAddEntID(system, it->first, it->second)) {
        it = m_ents.erase(it);
      } else if (m_br->tryAddEntID(system, it->first, it->second)) {
        it = m_ents.erase(it);
      } else {
        it++;
      }
    }
  }

  if (m_ents.size() == 0) {
    if (this->m_parent && this->m_parent->m_ents.size() == 0 &&
        this->m_parent->m_tl && this->m_parent->m_tl->m_tl == nullptr &&
        this->m_parent->m_tr->m_tl == nullptr &&
        this->m_parent->m_bl->m_tl == nullptr &&
        this->m_parent->m_br->m_tl == nullptr &&
        this->m_parent->m_tl->m_ents.size() == 0 &&
        this->m_parent->m_tr->m_ents.size() == 0 &&
        this->m_parent->m_bl->m_ents.size() == 0 &&
        this->m_parent->m_br->m_ents.size() == 0) {
      // if this is a leaf and its parent and siblings have 0 entIDs,
      // delete this and its siblings
      m_parent->m_tl.reset(nullptr);
      m_parent->m_tr.reset(nullptr);
      m_parent->m_bl.reset(nullptr);
      m_parent->m_br.reset(nullptr);
    }
  }
}

void TdCollisionQuadTreeNode::getAllWithinRadius(
    TdECSSystem *system, std::vector<TdECSEntity *> &ents, double x, double y,
    double r) {
  if (m_tl) {
    if (m_tl->m_rect.cheapIntersectsCircle(glm::dvec2(x, y), r)) {
      m_tl->getAllWithinRadius(system, ents, x, y, r);
    }
    if (m_tr->m_rect.cheapIntersectsCircle(glm::dvec2(x, y), r)) {
      m_tr->getAllWithinRadius(system, ents, x, y, r);
    }
    if (m_bl->m_rect.cheapIntersectsCircle(glm::dvec2(x, y), r)) {
      m_bl->getAllWithinRadius(system, ents, x, y, r);
    }
    if (m_br->m_rect.cheapIntersectsCircle(glm::dvec2(x, y), r)) {
      m_br->getAllWithinRadius(system, ents, x, y, r);
    }
  }

  for (auto entID : m_ents) {
    glm::dvec2 entp = entID.second->getPosition();

    double dist =
        std::sqrt((x - entp.x) * (x - entp.x) + (y - entp.y) * (y - entp.y));

    if (dist <= r) {
      ents.push_back(entID.second);
    }
  }
}

int TdCollisionQuadTreeNode::getNumEnts() {
  int num = m_ents.size();
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
