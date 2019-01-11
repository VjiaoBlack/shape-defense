
#include "Game.hpp"
#include "TdRenderLoop/GameLoop.hpp"
#include "TdRenderLoop/MainMenuLoop.hpp"

#include <deque>
#include <TdECS/Entity.hpp>

#include <Graphics.hpp>

set<int>  Game::m_keysDown;
set<int>  Game::m_keysDownPrev;
set<char> Game::m_buttonsDown;
set<char> Game::m_buttonsDownPrev;

double Game::m_mouseX;
double Game::m_mouseY;

Game::Game()
    : m_quit(false),
      m_gameStateTransition(nullptr),
      m_deltaTime(0),
      m_frames(0),
      m_frameRate(30) {
  graphicsBackend.initialize();


  // initialize framerate counter
  m_deltaTime = 0;
  m_frames = 0;
  m_frameRate = 30;

  // use glfw callbacks
  glfwSetKeyCallback(graphicsBackend.window, Game::key_callback);
  glfwSetCursorPosCallback(graphicsBackend.window, Game::cursor_pos_callback);
  glfwSetMouseButtonCallback(graphicsBackend.window, Game::mouse_button_callback);

  // setup entities
  m_entitySystem = make_unique<System>();
  Entity::addEntity<EntityType::BASE>(this, m_entitySystem.get());

  // setup game loop
//  auto tempmenu = make_shared<MainMenuLoop>(this);
  auto tempmenu = make_shared<GameLoop>(this);
  m_gameStateStack.push_back(std::move(tempmenu));

}

Game::~Game() {
  while (!m_gameStateStack.empty()) {
    m_gameStateStack.pop_back();
  }

  graphicsBackend.destroy();
}


void Game::run() {
  while (!m_quit) {

    // TODO: consider GLFW time?
    clock_t beginFrame = clock();

    // Update keysDown and buttonsDown
    handleInput();

    if (m_gameStateTransition) {
      m_gameStateTransition->render(this);
      RenderLoop *loop = m_gameStateTransition->update(this);
      if (!loop) {
        m_gameStateTransition.reset(nullptr);
      }
    } else {
      m_gameStateStack.back()->render(this);
      RenderLoop *loop = m_gameStateStack.back()->update(this);
    }

    // update screen
    clock_t endFrame = clock();

    m_deltaTime = clockToMilliseconds(endFrame - beginFrame);
    double rfps = (1000.0 / m_deltaTime);
    // display rFPS (rendering FPS)
//    std::cout << "rFPS: " << rfps << std::endl;
    fflush(stdout);
    if (m_deltaTime < (1000.0 / 30.0)) {
      usleep(1000 * ((1000.0 / 30.0) - m_deltaTime));
      m_deltaTime = 1000 / 30.0;
    }

    if (glfwWindowShouldClose(graphicsBackend.window)) {
      m_quit = true;
    }
  }
}

// TODO: Assuming that order of processing doesn't matter??
// TODO: will these happen in-between processing entity updates?
void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    m_keysDown.insert(key);
  } else if (action == GLFW_RELEASE) {
    m_keysDown.erase(key);
  }
}

void Game::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
  Game::m_mouseX = xpos;
  Game::m_mouseY = ypos;
}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  if (action == GLFW_PRESS) {
    m_buttonsDown.insert(button);
  } else if (action == GLFW_RELEASE) {
    m_buttonsDown.erase(button);
  }
}

void Game::handleInput() {
  Game::m_keysDownPrev.empty();
  Game::m_buttonsDownPrev.empty();
  Game::m_keysDownPrev = m_keysDown;
  Game::m_buttonsDownPrev = m_buttonsDown;
}
