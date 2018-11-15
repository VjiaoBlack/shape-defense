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
  m_root->refreshNode(game, system, m_root->m_ents);
  LOG_VRB("QuadTree Sz: %d  | Lvl: %d", m_root->getNumEnts(), m_root->getDeepestLayer(0));
}

bool TdCollisionQuadTree::tryAddEntID(TdGame *game,
                                      TdECSSystem *system,
                                      int entID,
                                      TdECSEntity *ent) {
  return m_root->tryAddEntID(system, entID, ent);
}

void TdCollisionQuadTree::removeEntID(TdGame *game, TdECSSystem *system, int entID) {
  m_root->removeEntID(system, entID);
}