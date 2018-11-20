#pragma once
/**
 * TdECSFighterComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Component.hpp"

class Fighter : public Component {
 public:
  Fighter() {};

  virtual void update(Game *game, System *system);
};

