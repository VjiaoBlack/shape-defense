#pragma once
/**
 * TdECSGraphicsComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Component.hpp"
#include <Utils.hpp>

class Game;
class System;

class Graphics : public Component {
 public:
  MY_Color m_color{};

  Triangle m_laser;
  bool m_validIndices = false;

  Graphics() {}
  Graphics(MY_Color color) : m_color(color) {}

  void destroy() {
    m_laser.destroy();
    m_validIndices = false;
  }

  void update(Game* game, System* system);
};

