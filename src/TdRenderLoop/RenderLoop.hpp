#pragma once

/**
 * TdRenderLoop.hpp
 *
 * Includes information about rendering loops
 */

#include <set>

//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <iostream>
#include <random>
#include <vector>

#include "Game.hpp"

class RenderLoop {
 public:
  RenderLoop() = default;
  virtual ~RenderLoop() = default;

  inline virtual RenderLoop *update(Game *game) { return this; };
  inline virtual void render(Game *game) {};
};