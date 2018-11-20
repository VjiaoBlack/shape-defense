/**
 * defense.cpp
 *
 * Victor Jiao
 *
 *
 */

#define GLM_SWIZZLE
#define GLM_INLINE

#include "Game.hpp"

int main(int argv, char *argc[]) {
  shared_ptr<Game> renderer = make_shared<Game>();
  renderer->run();
  renderer.reset();
  TTF_Quit();
  SDL_Quit();
  return 0;
}