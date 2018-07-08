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
#include <glm/vec2.hpp>

class TdGame;
class TdECSSystem;
class TdECSEntity;

class TdECSShapeComponent;

struct TdECSRect {
  glm::dvec2 pos;
  double w;
  double h;

  TdECSRect(glm::dvec2 _pos, double _w, double _h) : pos(_pos), w(_w), h(_h) {};
  bool contains(TdECSEntity* ent);
};

struct TdECSSegment {
  glm::dvec2 p1;
  glm::dvec2 p2;

  TdECSSegment(glm::dvec2 _p1, glm::dvec2 _p2) : p1(_p1), p2(_p2) {};
  bool intersects(TdECSSegment segment);
};

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
