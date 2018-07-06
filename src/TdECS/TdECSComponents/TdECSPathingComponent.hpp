#pragma once
/** 
 * TdECSPathingComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSComponent.hpp"

// uses TdECSCollisionSystem heavily.
class TdECSPathingComponent : public TdECSComponent {
 public:
  bool m_isMoving = false;
  double m_goalX = 0;
  double m_goalY = 0;

  void move(TdGame* game, TdECSSystem* system, double x, double y);

  void stop(TdGame* game, TdECSSystem* system);

  virtual void update(TdGame* game, TdECSSystem* system);
};

