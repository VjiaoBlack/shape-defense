#pragma once

/**
 * TdRenderLoop.hpp
 *
 * Includes information about rendering loops
 */

#include <set>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

#include "../TdGame.hpp"

class TdRenderLoop {
 public:
  TdRenderLoop() = default;
  virtual ~TdRenderLoop() = default;

  inline virtual TdRenderLoop *update(TdGame *game) { return this; };
  inline virtual void render(TdGame *game) {};
};