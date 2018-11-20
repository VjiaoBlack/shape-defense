#pragma once
/**
 * TdECSGraphicsComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <SDL_pixels.h>
#include "Component.hpp"

class Graphics : public Component {
 public:
  SDL_Color m_color;
  Graphics(SDL_Color color) : m_color(color) {}
  virtual void update(Game *game, System *system);
};

