#pragma once
/**
 * TdECSSystemUtils.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <memory>
#include <vector>

class TdGame;
class TdECSSystem;
class TdECSEntity;

template <class T>
inline void updateComponents(TdGame* game, TdECSSystem* system,
                             std::vector<std::unique_ptr<T>>& vec) {
  for (auto c = vec.begin(); c != vec.end();) {
    if ((*c)->m_dead) {
      c = vec.erase(c);
    } else {
      (*c)->update(game, system);
      c++;
    }
  }
}

// TODO: use tuples? or use glm::vec2?
std::tuple<double, double> getCenterPosition(TdECSEntity *ent);
std::tuple<double, double> getPosition(TdECSEntity *ent);
double findCenterDistance(TdECSEntity* ent1, TdECSEntity* ent2);
std::tuple<double, double> findCenterDisplacement(TdECSEntity* ent1, TdECSEntity* ent2);