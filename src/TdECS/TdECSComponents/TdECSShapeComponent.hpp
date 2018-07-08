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
  double m_width;
  double m_height;

  std::vector<glm::dvec2> m_points;  // clockwise
  TdECSShapeComponent(double width, double height);
  virtual void update(TdGame *game, TdECSSystem *system) {}
};
