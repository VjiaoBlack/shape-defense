#pragma once
/**
 * TdECSTilePositionComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <glm/vec2.hpp>
#include "TdECSComponent.hpp"

class TdECSTilePositionComponent : public TdECSComponent {
 public:
  glm::ivec2 m_xy;

  TdECSTilePositionComponent(int x, int y)
      : m_xy(x, y) {};

  virtual void update(TdGame *game, TdECSSystem *system) {}
};
