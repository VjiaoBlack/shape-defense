#pragma once
/**
 * TdECSPhysicsComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <glm/vec2.hpp>
#include "Component.hpp"

class Physics : public Component {
 public:
  glm::vec2 m_v = {};
  double m_vtheta = 0.0;

  Physics() {}
};
