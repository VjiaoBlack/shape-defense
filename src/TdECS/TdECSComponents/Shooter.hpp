#pragma once
/**
 * TdECSShooterComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Component.hpp"

class Shooter : public Component {
 public:
  Shooter() {};
  virtual void update(Game *game, System *system);
};
