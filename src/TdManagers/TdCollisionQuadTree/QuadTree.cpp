/** q
 * TdCollisionQuadTree.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "QuadTree.hpp"
#include "Node.hpp"
#include "Game.hpp"
#include "ECS/Entity.hpp"

void QuadTree::print(System* system, Game* game) {
  m_root->print( system, game);
}

void QuadTree::update(Game *game, System *system) {
  m_root->refreshNode(game, system, m_root->m_ents);
  LOG_VRB("QuadTree Sz: %d  | Lvl: %d", m_root->getNumEnts(), m_root->getDeepestLayer(0));
}

bool QuadTree::tryAddEntID(Game *game, System *system,
                           int entID) {
  return m_root->tryAddEntID(system, entID);
}

void QuadTree::removeEntID(Game *game, System *system, int entID) {
//  printf("Removing id %d", entID);
  m_root->removeEntID(system, entID);
}