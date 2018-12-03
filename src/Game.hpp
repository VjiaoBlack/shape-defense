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

#include "Graphics.hpp"
#include "TdECS/TdECSSystems/System.hpp"

using namespace std;

class GameLoop;
class MainMenuLoop;
class RenderLoop;

class Game {
 public:
  Window   m_SDLWindow;
  Renderer m_SDLRenderer;

  // setup for rendering loop
  SDL_Event m_SDLEvent;
  bool      m_quit;

  set<int>  m_keysDown;
  set<int>  m_keysDownPrev;
  set<char> m_buttonsDown;
  set<char> m_buttonsDownPrev;

  int m_mouseX;
  int m_mouseY;

  ttf_font_pt m_font     = SDL::null_font();
  ttf_font_pt m_menuFont = SDL::null_font();

  std::unique_ptr<RenderLoop>            m_gameStateTransition;
  std::list<std::shared_ptr<RenderLoop>> m_gameStateStack;

  std::unique_ptr<System> m_entitySystem;

  // building values
  double m_curMoney  = 10.0;
  double m_maxMoney  = 120.0;
  double m_curEnergy = 0.0;
  double m_maxEnergy = 120.0;

  unsigned int m_frames;
  double       m_deltaTime;
  double       m_frameRate;

  Game();
  ~Game();

  void setupSDL();

  void handleInput();
  void handleKey(int SDLKey);
  void run();

  void mainMenu();
};
