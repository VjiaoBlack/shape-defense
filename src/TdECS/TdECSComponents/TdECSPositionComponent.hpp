#pragma once
/**
 * TdECSPositionComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <glm/vec2.hpp>
#include "TdECSComponent.hpp"

class TdECSPositionComponent : public TdECSComponent {
 public:
  glm::dvec2 m_p;

  TdECSPositionComponent(double x, double y)
      : m_p(x, y) {};

  virtual void update(TdGame *game, TdECSSystem *system) {}
};
