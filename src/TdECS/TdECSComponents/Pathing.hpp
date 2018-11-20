#pragma once
/** 
 * TdECSPathingComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <glm/vec2.hpp>
#include "Component.hpp"

// uses CollisionSystem heavily.
class Pathing : public Component {
 public:
  bool m_isMoving = false;
  glm::dvec2 m_goalxy;

  void move(Game* game, System* system, double x, double y);

  void stop(Game* game, System* system);

  virtual void update(Game* game, System* system);
};

