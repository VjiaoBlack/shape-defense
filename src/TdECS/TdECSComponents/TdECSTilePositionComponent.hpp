#pragma once
/**
 * TdECSTilePositionComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSComponent.hpp"

class TdECSTilePositionComponent : public TdECSComponent {
 public:
  int m_x;
  int m_y;

  TdECSTilePositionComponent(int x, int y)
      : m_x(x), m_y(y) {};

  virtual void update(TdGame *game) {}
};
