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

  std::array<int, 9> m_effectIndices;
  bool m_validIndices = false;

  Graphics() {}
  Graphics(MY_Color color) : m_color(color) {}

  void update(Game* game, System* system);
};

