/**
 * TdCollisionQuadTreeNode.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "Node.hpp"
#include <TdECS/TdECSSystems/SystemPosUtils.hpp>
#include <Game.hpp>
#include <csignal>
#include "TdECS/Entity.hpp"
#include "QuadTree.hpp"

void Node::getAdjacentNodes(
    list<Node *> &nodes) {
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

Node *Node::getContainingNode(
    System *system, int entID) {
  auto ent = system->getEnt(entID);

//  TODO: this is only to stop breaking when we can't find an ent on remove
  if (ent == nullptr) {
    return nullptr;
  }
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
    return this;
  } else {
    return nullptr;
  }
}

Node *Node::forceSearch(System *system, int entID) {
//  LOG_ERR("dim: %f, %f: %f, %f", m_rect.pos.x, m_rect.pos.y,
//                                 m_rect.pos.x + m_rect.w,
//                                 m_rect.pos.y + m_rect.h);
  if (m_ents.count(entID)) {
    return this;
  }

  if (m_tl) {
    if (m_tl->m_ents.count(entID)) {
      return m_tl.get();
    } else {
      auto tmp = m_tl->forceSearch(system, entID);
      if (tmp) {
        return tmp;
      }
    }
    if (m_tr->m_ents.count(entID)) {
      return m_tr.get();
    } else {
      auto tmp = m_tr->forceSearch(system, entID);
      if (tmp) {
        return tmp;
      }
    }
    if (m_bl->m_ents.count(entID)) {
      return m_bl.get();
    } else {
      auto tmp = m_bl->forceSearch(system, entID);
      if (tmp) {
        return tmp;
      }
    }
    if (m_br->m_ents.count(entID)) {
      return m_br.get();
    } else {
      auto tmp = m_br->forceSearch(system, entID);
      if (tmp) {
        return tmp;
      }
    }
  }

  return nullptr;
}

bool Node::tryAddEntID(System *system, int entID) {
  auto node = getContainingNode(system, entID);

  if (node) {
    node->m_ents[entID] = system->getEnt(entID);
    return true;
  } else {
    return false;
  }
}

void Node::print(System* system, Game* game) {
  printf("%d: ", m_depth);

  for (auto entpair : m_ents) {
    printf("%d, ", entpair.first);
  }
  printf("\n");

  if (m_tl) m_tl->print(system, game);
  if (m_tr) m_tr->print(system, game);
  if (m_bl) m_bl->print(system, game);
  if (m_br) m_br->print(system, game);
}

void Node::removeEntID(System *system, int entID) {
  auto node = getContainingNode(system, entID);
  if (!node) {
    LOG_FAT("collision quad tree attempted to remove from nonexistent node. id: %d", entID);
    exit(1);
  }

  if (node->m_ents.count(entID) == 0) {
    LOG_FAT("collision quad tree attempted to remove ent from incorrect node. id: %d", entID);

    auto ent = system->getEnt(entID);
    // where the hell is it then???
    // TODO: need to fix
    // wait hold up, are they just not in the quadtree at all...
    // are we handling logic right if deleting an ent means deleting a bunch of nodes?
    node = system->m_collisions.m_qtree->m_root->forceSearch(system, entID);

    if (node) {
      printf("  FOUND %d, %d: %d, %d\n", (int)node->m_rect.pos.x,
             (int)node->m_rect.pos.y, (int)node->m_rect.w,
             (int)node->m_rect.h);

      LOG_ERR("%f, %f",
              system->getEnt(entID)->getPosition().x,
              system->getEnt(entID)->getPosition().y);

    } else {
      printf("NOT FOUND\n");
      exit(1);
    }

  }

  node->m_ents.erase(entID);
}

bool Node::containsEntID(System *system, int entID) {
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

void Node::refreshNode(
    Game *game, System *system,
    std::unordered_map<int, Entity *> &outside) {
  // draw rect
//  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0x80, 0x80, 0xFF, 0xFF);
//  SDL_Rect draw{(int)m_rect.pos.x, (int)m_rect.pos.y, (int)m_rect.w,
//                (int)m_rect.h};
//  SDL_RenderDrawRect(game->m_SDLRenderer, &draw);

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
      Rect newBaseRect = m_rect;
      newBaseRect.w /= 2.0;
      newBaseRect.h /= 2.0;

      Rect rectTL = newBaseRect;
      Rect rectTR = newBaseRect;
      Rect rectBL = newBaseRect;
      Rect rectBR = newBaseRect;

      rectTR.pos.x += m_rect.w / 2.0;
      rectBL.pos.y += m_rect.h / 2.0;
      rectBR.pos.x += m_rect.w / 2.0;
      rectBR.pos.y += m_rect.h / 2.0;

      this->m_tl =
          std::move(std::make_unique<Node>(this, rectTL));
      this->m_tr =
          std::move(std::make_unique<Node>(this, rectTR));
      this->m_bl =
          std::move(std::make_unique<Node>(this, rectBL));
      this->m_br =
          std::move(std::make_unique<Node>(this, rectBR));

      if (m_parent) {
        for (auto it = m_ents.begin(); it != m_ents.end(); it++) {
          if (!it->second->m_alive) {
            printf("SECRET DEAD\n");

            continue;
          }
          outside.insert(*it);
        }
        m_ents.clear();
      }
    }
  }

  // put non-fitting objects upwards
  if (m_parent && this) {
    for (auto it = m_ents.begin(); it != m_ents.end();) {
      if (it->second && it->second->m_alive && !this->m_rect.contains(it->second)) {
        outside.insert(*it);
//        printf("moved ! %d", it->first);
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
      if (!it->second->m_alive) {
        printf("SECRET DEAD\n");
        continue;
      }

      if (this->tryAddEntID(system, it->first)) {
        it = outside.erase(it);
      } else {
        it++;
      }
    }
  }

  // attempt to redistribute entIDs DOWN
  if (m_tl) {
    for (auto it = m_ents.begin(); it != m_ents.end();) {
      if (!it->second->m_alive) {
        continue;
      }

      // if entID is inside, put into m_ents
      if (m_tl->tryAddEntID(system, it->first)) {
        it = m_ents.erase(it);
      } else if (m_tr->tryAddEntID(system, it->first)) {
        it = m_ents.erase(it);
      } else if (m_bl->tryAddEntID(system, it->first)) {
        it = m_ents.erase(it);
      } else if (m_br->tryAddEntID(system, it->first)) {
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

      std::unique_ptr<Node>* reset = &m_parent->m_tl;
      if (m_parent->m_tl.get() != this) {
        m_parent->m_tl.reset(nullptr);
      }
      if (m_parent->m_tr.get() != this) {
        m_parent->m_tr.reset(nullptr);
      } else {
        reset = &m_parent->m_tr;
      }
      if (m_parent->m_bl.get() != this) {
        m_parent->m_bl.reset(nullptr);
      } else {
        reset = &m_parent->m_bl;
      }
      if (m_parent->m_br.get() != this) {
        m_parent->m_br.reset(nullptr);
      } else {
        reset = &m_parent->m_br;
      }

      (*reset).reset(nullptr);
    }
  }
}

void Node::getAllWithinRadius(
    System *system, std::vector<Entity *> &ents, double x, double y,
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
    if (!entID.second->m_alive) {
      continue;
    }

    glm::dvec2 entp = entID.second->getPosition();

    double dist =
        std::sqrt((x - entp.x) * (x - entp.x) + (y - entp.y) * (y - entp.y));

    if (dist <= r) {
      ents.push_back(entID.second);
    }
  }
}

int Node::getNumEnts() {
  int num = m_ents.size();
  if (m_tl) {
    num += m_tl->getNumEnts();
    num += m_tr->getNumEnts();
    num += m_bl->getNumEnts();
    num += m_br->getNumEnts();
  }
  return num;
}

int Node::getDeepestLayer(int start) {
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
