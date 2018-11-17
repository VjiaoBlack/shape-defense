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

  glm::vec4 r1(ent1->getPosition(),
               glm::vec2(ent1->get<TdECSShapeComponent>()->m_dimensions.x,
                         ent1->get<TdECSShapeComponent>()->m_dimensions.y));

  glm::vec4 r2(ent2->getPosition(),
               glm::vec2(ent2->get<TdECSShapeComponent>()->m_dimensions.x,
                         ent2->get<TdECSShapeComponent>()->m_dimensions.y));

  return intersect(r1, r2);
}

bool TdECSCollisionSystem::willCollide(TdECSSystem *system, TdECSEntity *ent1, TdECSEntity *ent2) {
  if (!ent1 || !ent2) {
    LOG_ERR("Collision system passed a Null ent.");
    return true;
  }

  double v1x = 0.0;
  double v1y = 0.0;
  double v2x = 0.0;
  double v2y = 0.0;

  bool moving1 = false;
  bool moving2 = false;

  if (ent1->has<TdECSPhysicsComponent>()) {
    moving1 = true;
    v1x = ent1->get<TdECSPhysicsComponent>()->m_vx;
    v1y = ent1->get<TdECSPhysicsComponent>()->m_vy;
  }
  if (ent2->has<TdECSPhysicsComponent>()) {
    moving2 = true;
    v2x = ent2->get<TdECSPhysicsComponent>()->m_vx;
    v2y = ent2->get<TdECSPhysicsComponent>()->m_vy;
  }
  glm::dvec2 ent1p = ent1->getPosition();
  glm::dvec2 ent2p = ent2->getPosition();

  double ent1x2 = v1x + ent1p.x + ent1->get<TdECSShapeComponent>()->m_dimensions.x;
  double ent1y2 = v1y + ent1p.y + ent1->get<TdECSShapeComponent>()->m_dimensions.y;

  double ent2x2 = v2x + ent2p.x + ent2->get<TdECSShapeComponent>()->m_dimensions.x;
  double ent2y2 = v2y + ent2p.y + ent2->get<TdECSShapeComponent>()->m_dimensions.y;

  bool willCollideBothFuture = ent1p.x <= ent2x2 && ent1x2 >= ent2p.x && ent1p.y <= ent2y2 &&
      ent1y2 >= ent2p.y;

  bool willCollide1Future = false;
  bool willCollide2Future = false;

  if (moving1) {
    ent1x2 = v1x + ent1p.x + ent1->get<TdECSShapeComponent>()->m_dimensions.x;
    ent1y2 = v1y + ent1p.y + ent1->get<TdECSShapeComponent>()->m_dimensions.y;

    ent2x2 = ent2p.x + ent2->get<TdECSShapeComponent>()->m_dimensions.x;
    ent2y2 = ent2p.y + ent2->get<TdECSShapeComponent>()->m_dimensions.y;

    willCollide1Future = ent1p.x <= ent2x2 && ent1x2 >= ent2p.x && ent1p.y <= ent2y2 &&
        ent1y2 >= ent2p.y;
  }

  if (moving2) {
    ent1x2 = ent1p.x + ent1->get<TdECSShapeComponent>()->m_dimensions.x;
    ent1y2 = ent1p.y + ent1->get<TdECSShapeComponent>()->m_dimensions.y;

    ent2x2 = v2x + ent2p.x + ent2->get<TdECSShapeComponent>()->m_dimensions.x;
    ent2y2 = v2y + ent2p.y + ent2->get<TdECSShapeComponent>()->m_dimensions.y;

    willCollide2Future = ent1p.x <= ent2x2 && ent1x2 >= ent2p.x && ent1p.y <= ent2y2 &&
        ent1y2 >= ent2p.y;
  }

  return willCollideBothFuture || willCollide1Future || willCollide2Future;
}
