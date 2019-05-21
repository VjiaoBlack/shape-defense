#pragma once
/**
 * TdECSShapeComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

//#include <SDL_rect.h>
#include "Component.hpp"

class Shape : public Component {
 public:
  glm::dvec2 m_dimensions;

  Shape() {}
  Shape(double width, double height)
      : m_dimensions(width, height) {}

  Shape(glm::vec2 dimensions)
      : m_dimensions(dimensions) {}
};
