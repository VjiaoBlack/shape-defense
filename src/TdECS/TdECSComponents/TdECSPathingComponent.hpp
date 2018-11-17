#pragma once
/** 
 * TdECSPathingComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <glm/vec2.hpp>
#include "TdECSComponent.hpp"

// uses TdECSCollisionSystem heavily.
class TdECSPathingComponent : public TdECSComponent {
 public:
  bool m_isMoving = false;
  glm::dvec2 m_goalxy;

  void move(TdGame* game, TdECSSystem* system, double x, double y);

  void stop(TdGame* game, TdECSSystem* system);

  virtual void update(TdGame* game, TdECSSystem* system);
};

