#pragma once
/**
 * TdECSCollisionSystem.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <memory>
#include <unordered_set>

class TdGame;
class TdECSEntity;
class TdECSSystem;
class TdCollisionQuadTree;

// allows hashing pairs
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator () (const std::pair<T1,T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);

    // temp hash function
    return h1 ^ h2;
  }
};

class TdECSCollisionSystem {
 public:
  TdCollisionQuadTree* m_qtree;

  // TODO: consider using bloom filter or something??
  std::unordered_set<std::pair<int, int>, pair_hash> m_collidingIds;

  TdECSCollisionSystem();

  ~TdECSCollisionSystem();

  void update(TdGame* game, TdECSSystem* system);

  // currently uses rectangle collisions
  bool isColliding(TdECSSystem* system, TdECSEntity* ent1, TdECSEntity* ent2);
  bool isColliding(TdECSSystem* system, TdECSEntity* ent);

  bool willCollide(TdECSSystem* system, TdECSEntity* ent1, TdECSEntity* ent2);
  bool willCollide(TdECSSystem* system, TdECSEntity* ent);
};
