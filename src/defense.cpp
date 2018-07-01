/**
 * defense.cpp
 *
 * Victor Jiao
 *
 *
 */

#include "TdGame.hpp"

int main(int argv, char *argc[]) {
  shared_ptr<TdGame> renderer = make_shared<TdGame>();
  renderer->run();
  renderer.reset();
  TTF_Quit();
  SDL_Quit();
  return 0;
}