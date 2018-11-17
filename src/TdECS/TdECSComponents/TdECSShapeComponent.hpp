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
#include "../TdECSSystems/TdECSSystemUtils.hpp"
#include "TdECSComponent.hpp"

class TdECSShapeComponent : public TdECSComponent {
 public:
  glm::dvec2 m_dimensions;

  TdECSShapeComponent(double width, double height);
  TdECSShapeComponent(glm::vec2 dimensions);
  virtual void update(TdGame *game, TdECSSystem *system) {}
};
