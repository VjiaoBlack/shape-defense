#pragma once
/**
 * TdCollisionQuadTreeNode.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <SDL_rect.h>
#include <unordered_map>
#include <set>
#include <list>
#include <TdECS/TdECSSystems/TdECSRect.hpp>
#include "../../TdECSSystems/TdECSSystemUtils.hpp"

class TdGame;
class TdECSSystem;

class TdCollisionQuadTreeNode {
 public:
  std::unordered_map<int, TdECSEntity *> m_ents;
  int m_depth;
  TdCollisionQuadTreeNode *m_parent = nullptr;

  TdCollisionQuadTreeNode *getContainingNode(TdECSSystem *system, int entID);
  TdCollisionQuadTreeNode *forceSearch(TdECSSystem *system, int entID);

  TdECSRect m_rect;

  std::unique_ptr<TdCollisionQuadTreeNode> m_tl;
  std::unique_ptr<TdCollisionQuadTreeNode> m_tr;
  std::unique_ptr<TdCollisionQuadTreeNode> m_bl;
  std::unique_ptr<TdCollisionQuadTreeNode> m_br;

  TdCollisionQuadTreeNode(TdCollisionQuadTreeNode *parent, TdECSRect rect)
      : m_parent(parent), m_rect(rect) {
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

  ~TdCollisionQuadTreeNode() {}

  bool containsEntID(TdECSSystem *system, int entID);
  void refreshNode(TdGame *game, TdECSSystem *system,
                   std::unordered_map<int, TdECSEntity *> &outside);
  void getAllWithinRadius(TdECSSystem *system,
                          std::vector<TdECSEntity *> &ents,
                          double x, double y, double r);

  bool tryAddEntID(TdECSSystem *system, int entID, TdECSEntity *ent);
  void removeEntID(TdECSSystem *system, int entID);

  void getAdjacentNodes(std::list<TdCollisionQuadTreeNode *> &nodes);

  int getNumEnts();
  int getDeepestLayer(int start);
};
