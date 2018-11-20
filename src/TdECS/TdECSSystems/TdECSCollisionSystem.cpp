/** 
 * TdECSCollisionSystem.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSCollisionSystem.hpp"

#include <TdECS/TdECSSystems/TdCollisionQuadTree/TdCollisionQuadTreeNode.hpp>
#include "TdCollisionQuadTree/TdCollisionQuadTree.hpp"

bool intersect(glm::vec4 r1, glm::vec4 r2) {
  return r1.x <= r2.z + r2.x && r1.x + r1.w >= r2.x && r1.y <= r2.y + r2.w &&
      r1.y + r1.w >= r2.y;
}

TdECSCollisionSystem::TdECSCollisionSystem() {
  m_qtree = new TdCollisionQuadTree();
}

TdECSCollisionSystem::~TdECSCollisionSystem() {
  delete m_qtree;
}

void TdECSCollisionSystem::update(TdGame *game, TdECSSystem *system) {
  m_qtree->update(game, system);

  m_collidingIds.clear();
  m_collidingIdsSingle.clear();
  m_closestDeltas.clear();

  std::list<TdCollisionQuadTreeNode *> node_path;
  std::list<TdCollisionQuadTreeNode *> node_stack; // depth, node*

  // go from root downwards with Depth First Traversal
  // for every node, intersect all ents with ents of nodes in path_to_root
  // keep track of colliding pairs, don't look at those twice

  // use nullpointer to indicate pop node

  node_stack.push_front(m_qtree->m_root.get());

  while (node_stack.size() > 0) {
    // wishing for C++17 structured bindings
    auto cur_node = node_stack.front();

    if (node_path.size() - 1 == cur_node->m_depth) {
      node_path.pop_front();
      continue;
    } else {
      node_stack.pop_front();
      node_path.push_front(cur_node);

      if (cur_node->m_tl != nullptr) {
        node_stack.push_front(cur_node->m_tl.get());
        node_stack.push_front(cur_node->m_tr.get());
        node_stack.push_front(cur_node->m_bl.get());
        node_stack.push_front(cur_node->m_br.get());
      }
    }

    // intersect all current ents with ents of nodes in path_to_root;

    for (auto node : node_path) {
      for (auto ent1 : node->m_ents) {
        for (auto ent2 : cur_node->m_ents) {
          if (ent1.first != ent2.first &&
              willCollide(system, ent1.second, ent2.second)) {
            m_collidingIds.insert(std::make_pair(std::min(ent1.first, ent2.first),
                                            std::max(ent1.first, ent2.first)));
            m_collidingIdsSingle.insert(ent1.first);
            m_collidingIdsSingle.insert(ent2.first);

            glm::vec2 disp = ent2.second->getPosition() -
                             ent1.second->getPosition();
            double dist = glm::max(glm::abs(disp.x), glm::abs(disp.y));

            if (m_closestDeltas.find(ent1.first) == m_closestDeltas.end() ||
                dist < glm::max(glm::abs(m_closestDeltas[ent1.first].x),
                                glm::abs(m_closestDeltas[ent1.first].y))) {
              m_closestDeltas[ent1.first] = disp;
            }

            if (m_closestDeltas.find(ent2.first) == m_closestDeltas.end() ||
                dist < glm::max(glm::abs(m_closestDeltas[ent2.first].x),
                                glm::abs(m_closestDeltas[ent2.first].y))) {
              m_closestDeltas[ent2.first] = -disp;
            }
          }
        }
      }
    }
    if (cur_node->m_tl == nullptr) {
      node_path.pop_front();
    }
  }
}

bool TdECSCollisionSystem::isColliding(TdECSSystem *system, TdECSEntity *ent1, TdECSEntity *ent2) {
  if (!ent1 || !ent2) {
    LOG_ERR("Collision system passed a Null ent.");
    return true;
  }

  glm::vec4 r1(ent1->getPosition(), ent1->get<TdECSShapeComponent>()->m_dimensions);
  glm::vec4 r2(ent2->getPosition(), ent2->get<TdECSShapeComponent>()->m_dimensions);

  return intersect(r1, r2);
}

bool TdECSCollisionSystem::willCollide(TdECSSystem *system, TdECSEntity *ent1, TdECSEntity *ent2) {
  if (!ent1 || !ent2) {
    LOG_ERR("Collision system passed a Null ent.");
    return true;
  }

  glm::dvec2 v1(0.0);
  glm::dvec2 v2(0.0);

  bool moving1 = false;
  bool moving2 = false;

  if (ent1->has<TdECSPhysicsComponent>()) {
    moving1 = true;
    v1 = ent1->get<TdECSPhysicsComponent>()->m_v;
  }
  if (ent2->has<TdECSPhysicsComponent>()) {
    moving2 = true;
    v2 = ent2->get<TdECSPhysicsComponent>()->m_v;
  }
  glm::dvec2 ent1p = ent1->getPosition();
  glm::dvec2 ent2p = ent2->getPosition();

  bool willCollideBothFuture = intersect(
      glm::dvec4(v1 + ent1p, ent1->get<TdECSShapeComponent>()->m_dimensions),
      glm::dvec4(v2 + ent2p, ent2->get<TdECSShapeComponent>()->m_dimensions));

  bool willCollide1Future = false;
  bool willCollide2Future = false;

  if (moving1) {
    willCollide1Future = intersect(
        glm::dvec4(v1 + ent1p, ent1->get<TdECSShapeComponent>()->m_dimensions),
        glm::dvec4(ent2p, ent2->get<TdECSShapeComponent>()->m_dimensions));
  }

  if (moving2) {
    willCollide2Future = intersect(
        glm::dvec4(ent1p, ent1->get<TdECSShapeComponent>()->m_dimensions),
        glm::dvec4(v2 + ent2p, ent2->get<TdECSShapeComponent>()->m_dimensions));
  }

  return willCollideBothFuture || willCollide1Future || willCollide2Future;
}
