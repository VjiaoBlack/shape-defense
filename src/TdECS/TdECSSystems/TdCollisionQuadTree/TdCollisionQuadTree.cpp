/** 
 * TdCollisionQuadTree.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdCollisionQuadTree.hpp"
#include "TdCollisionQuadTreeNode.hpp"
#include "../../../TdGame.hpp"
#include "../../TdECSEntity.hpp"


void TdCollisionQuadTree::update(TdGame *game, TdECSSystem *system) {
  m_root->refreshNode(game, system, m_root->m_entIDs);
//  printf("\n");
//  printf("QuadTree Sz: %d\n", m_root->getNumEnts());
//  printf("QuadTre Lvl: %d\n", m_root->getDeepestLayer(0));
}

bool TdCollisionQuadTree::tryAddEntID(TdGame *game, TdECSSystem *system, int entID) {
  return m_root->tryAddEntID(game, system, entID);
}

void TdCollisionQuadTree::removeEntID(TdGame *game, TdECSSystem *system, int entID) {
  m_root->removeEntID(game, system, entID);
}