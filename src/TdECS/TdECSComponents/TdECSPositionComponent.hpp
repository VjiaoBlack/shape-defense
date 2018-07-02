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
  double m_theta;  // clockwise from north

  TdECSPositionComponent(double x, double y, double theta)
      : m_x(x), m_y(y), m_theta(theta){};

  virtual void update(TdGame *game, TdECSSystem *system) {}
};
