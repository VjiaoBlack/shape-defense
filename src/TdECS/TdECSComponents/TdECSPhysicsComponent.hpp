#pragma once
/**
 * TdECSPhysicsComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <glm/vec2.hpp>
#include "TdECSComponent.hpp"

class TdECSPhysicsComponent : public TdECSComponent {
 public:
  glm::vec2 m_v = {};
  double m_vtheta = 0.0;

  TdECSPhysicsComponent() {}

  virtual void update(TdGame *game, TdECSSystem *system);
};
