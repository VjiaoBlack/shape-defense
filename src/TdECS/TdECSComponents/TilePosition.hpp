#pragma once
/**
 * TdECSTilePositionComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <glm/vec2.hpp>
#include "Component.hpp"

class TilePosition : public Component {
 public:
  glm::ivec2 m_xy;

  TilePosition() {}
  TilePosition(int x, int y)
      : m_xy(x, y) {};
};
