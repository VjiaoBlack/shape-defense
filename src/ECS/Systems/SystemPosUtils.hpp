#pragma once
/**
 * TdECSSystemPosUtils.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "ECS/Entity.hpp"



inline double findCenterDistance(Entity& ent1, Entity& ent2) {
  glm::dvec2 ent1p = ent1.getCenterPosition();
  glm::dvec2 ent2p = ent2.getCenterPosition();

  return sqrt((ent1p.x - ent2p.x) * (ent1p.x - ent2p.x) +
              (ent1p.y - ent2p.y) * (ent1p.y - ent2p.y));
}

inline glm::dvec2 findCenterDisplacement(Entity& ent1, Entity& ent2) {
  glm::dvec2 ent1p = ent1.getCenterPosition();
  glm::dvec2 ent2p = ent2.getCenterPosition();

  return glm::dvec2(ent2p.x - ent1p.x, ent2p.y - ent1p.y);
};
