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
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/detail/_swizzle.hpp>

class Game;
class System;
class Entity;

class Shape;

constexpr uint16_t k_MAX_ENTS = 512;

struct TdECSSegment {
  glm::dvec2 p1;
  glm::dvec2 p2;

  TdECSSegment(glm::dvec2 _p1, glm::dvec2 _p2) : p1(_p1), p2(_p2) {};
  bool intersects(TdECSSegment segment);
};

template <class T>
inline void updateComponents(Game* game, System* system,
                             std::vector<std::unique_ptr<T>>& vec) {
  for (auto c = vec.begin(); c != vec.end();) {
    if (!(*c)->m_alive) {
      c = vec.erase(c);
    } else {
      (*c)->update(game, system);
      c++;
    }
  }
}
