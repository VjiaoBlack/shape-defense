#pragma once
/**
 * TdECSGraphicsComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <SDL_pixels.h>
#include "TdECSComponent.hpp"

class TdECSGraphicsComponent : public TdECSComponent {
 public:
  SDL_Color m_color;
  TdECSGraphicsComponent(SDL_Color color) : m_color(color) {}
  virtual void update(TdGame* game);
};

