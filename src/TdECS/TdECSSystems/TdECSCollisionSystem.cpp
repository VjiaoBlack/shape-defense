/** 
 * TdECSCollisionSystem.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSCollisionSystem.hpp"

#include "TdCollisionQuadTree/TdCollisionQuadTree.hpp"

TdECSCollisionSystem::TdECSCollisionSystem() {
  m_qtree = new TdCollisionQuadTree();
}

TdECSCollisionSystem::~TdECSCollisionSystem() {
  delete m_qtree;
}



void TdECSCollisionSystem::update(TdGame* game, TdECSSystem* system) {
  m_qtree->update(game, system);
}