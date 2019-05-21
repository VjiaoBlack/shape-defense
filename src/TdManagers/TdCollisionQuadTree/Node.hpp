#pragma once
/**
 * TdCollisionQuadTreeNode.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

//#include <SDL_rect.h>
#include <unordered_map>
#include <set>
#include <list>
#include <ECS/Systems//Rect.hpp>
#include "ECS/Systems//SystemUtils.hpp"

class Game;
class System;

class Node {
 public:
  std::unordered_map<int, Entity *> m_ents;
  int m_depth;
  Node *m_parent = nullptr;

  Node *getContainingNode(System *system, int entID);
  Node *forceSearch(System *system, int entID);

  Rect m_rect;

  std::unique_ptr<Node> m_tl;
  std::unique_ptr<Node> m_tr;
  std::unique_ptr<Node> m_bl;
  std::unique_ptr<Node> m_br;

  Node(Node *parent, Rect rect)
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

  ~Node() {}
  void print (System* system, Game* game);

  bool containsEntID(System *system, int entID);
  void refreshNode(Game *game, System *system,
                   std::unordered_map<int, Entity *> &outside);
  void getAllWithinRadius(System *system,
                          std::vector<Entity *> &ents,
                          double x, double y, double r);

  bool tryAddEntID(System *system, int entID);
  void removeEntID(System *system, int entID);

  void getAdjacentNodes(std::list<Node *> &nodes);

  int getNumEnts();
  int getDeepestLayer(int start);
};
