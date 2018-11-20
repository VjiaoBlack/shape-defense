#pragma once
/**
 * TdECSShapeComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <SDL_rect.h>
#include <vector>
#include "TdECS/TdECSSystems/SystemUtils.hpp"
#include "Component.hpp"

class Shape : public Component {
 public:
  glm::dvec2 m_dimensions;

  Shape(double width, double height);
  Shape(glm::vec2 dimensions);
  virtual void update(Game *game, System *system) {}
};
