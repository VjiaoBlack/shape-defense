#pragma once
/**
 * TdECSPositionComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <glm/vec2.hpp>
#include "Component.hpp"

class Position : public Component {
 public:
  glm::dvec2 m_p;

  Position(double x, double y)
      : m_p(x, y) {};
};
