#pragma once

#include <set>

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

// TODO: enforce singleton
class Game {
 public:
  bool m_quit;

  static set<int>  m_keysDown;
  static set<int>  m_keysDownPrev;
  static set<char> m_buttonsDown;
  static set<char> m_buttonsDownPrev;

  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
  static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

  static double m_mouseX;
  static double m_mouseY;

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

  void updatePrevInput();
  void handleKey(int SDLKey);
  void run();

  void mainMenu();
};


