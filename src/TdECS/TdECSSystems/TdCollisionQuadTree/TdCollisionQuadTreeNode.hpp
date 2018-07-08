#pragma once
/**
 * TdCollisionQuadTreeNode.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <SDL_rect.h>
#include <set>
#include "../../TdECSSystems/TdECSSystemUtils.hpp"

class TdGame;
class TdECSSystem;

class TdCollisionQuadTreeNode {
 public:
  std::set<int> m_entIDs;
  int m_depth;
  TdCollisionQuadTreeNode *m_parent = nullptr;

  TdCollisionQuadTreeNode *getContainingNode(TdGame *game, TdECSSystem *system,
                                             int entID);
  TdCollisionQuadTreeNode *forceSearch(TdGame *game, TdECSSystem *system,
                                             int entID);

  TdECSRect m_rect;

  std::unique_ptr<TdCollisionQuadTreeNode> m_tl;
  std::unique_ptr<TdCollisionQuadTreeNode> m_tr;
  std::unique_ptr<TdCollisionQuadTreeNode> m_bl;
  std::unique_ptr<TdCollisionQuadTreeNode> m_br;

  TdCollisionQuadTreeNode(TdCollisionQuadTreeNode *parent, TdECSRect rect)
      : m_parent(parent), m_rect(rect){
    m_tl.reset(nullptr);
    m_tr.reset(nullptr);
    m_bl.reset(nullptr);
    m_br.reset(nullptr);

    if (parent) {
      m_depth = parent->m_depth + 1;
    } else {
      m_depth = 0;
    }
  };

  ~TdCollisionQuadTreeNode() {
  }

  bool containsEntID(TdGame *game, TdECSSystem *system, int entID);
  void refreshNode(TdGame *game, TdECSSystem *system, std::set<int>& outside);
  void getAllWithinRadius(TdGame *game, TdECSSystem *system,
                          std::set<int> &ents, double x, double y, double r);

  bool tryAddEntID(TdGame *game, TdECSSystem *system, int entID);
  void removeEntID(TdGame *game, TdECSSystem *system, int entID);

  int getNumEnts();
  int getDeepestLayer(int start);
};
