#pragma once
/**
 * TdECSGraphicsComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Component.hpp"

class Graphics : public Component {
 public:
  SDL_Color m_color{};

  Graphics() {}
  Graphics(SDL_Color color) : m_color(color) {}
};

