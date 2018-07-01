#pragma once

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
#include <iterator>
#include <list>
#include <random>
#include <vector>
#include <memory>

#include "TrGraphics.hpp"
#include "TdECS/TdECSSystems/TdECSSystem.hpp"

using namespace std;

class TdGameLoop;
class TrMainMenuLoop;
class TdRenderLoop;
class TdEntitySystem;

class TdGame {
 public:
  TrWindow m_SDLWindow;

  TrRenderer m_SDLRenderer;

  // setup for rendering loop
  SDL_Event m_SDLEvent;
  bool m_quit;

  set<int> m_keysDown;
  set<int> m_keysDownPrev;
  set<char> m_buttonsDown;
  set<char> m_buttonsDownPrev;
  int m_mouseX;
  int m_mouseY;

  ttf_font_pt m_font = TrSDL::null_font();
  ttf_font_pt m_menuFont = TrSDL::null_font();

  std::unique_ptr<TdRenderLoop> m_gameStateTransition;
  std::list<shared_ptr<TdRenderLoop>> m_gameStateStack;

  std::unique_ptr<TdECSSystem> m_entitySystem;

  // framerate counter
  double m_deltaTime;
  unsigned int m_frames;
  double m_frameRate;

  TdGame();
  ~TdGame();

  void setupSDL();

  void handleInput();
  void handleKey(int SDLKey);
  void run();

  void mainMenu();
};
