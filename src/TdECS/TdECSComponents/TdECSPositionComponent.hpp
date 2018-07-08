#pragma once
/**
 * TdECSPositionComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSComponent.hpp"

class TdECSPositionComponent : public TdECSComponent {
 public:
  double m_x;
  double m_y;

  TdECSPositionComponent(double x, double y)
      : m_x(x), m_y(y){};

  virtual void update(TdGame *game, TdECSSystem *system) {}
};
