/**
 * TdGameLoop.cpp
 */

#include "GameLoop.hpp"
#include <TdManagers/ConstructionManager.hpp>
#include <TdManagers/LevelManager.hpp>
#include "TdECS/Entity.hpp"
#include "MainMenuLoop.hpp"
#include "TransitionLoop.hpp"

class MainMenuLoop;

void addTriangle(std::vector<GLfloat>& buf, int pos, glm::vec2 a, glm::vec2 b, glm::vec2 c) {
  graphicsBackend.entVBOdata[pos + 0] = a.x;
  graphicsBackend.entVBOdata[pos + 1] = a.y;
  graphicsBackend.entVBOdata[pos + 2] = 0.0f;

  graphicsBackend.entVBOdata[pos + 3] = b.x;
  graphicsBackend.entVBOdata[pos + 4] = b.y;
  graphicsBackend.entVBOdata[pos + 5] = 0.0f;

  graphicsBackend.entVBOdata[pos + 6] = c.x;
  graphicsBackend.entVBOdata[pos + 7] = c.y;
  graphicsBackend.entVBOdata[pos + 8] = 0.0f;
}


GameLoop::GameLoop(Game *game) {
  m_constructionManager = std::make_unique<ConstructionManager>(game);
  m_levelManager = std::make_unique<LevelManager>(game);

  // draw money
  m_moneyBar1 = Triangle(&graphicsBackend.guiVBOdata,
                     &graphicsBackend.guicolorVBOdata,
                     glm::vec2(50, K_DISPLAY_SIZE_Y - 50),
                     glm::vec2(50, K_DISPLAY_SIZE_Y - 75),
                     glm::vec2(50 + (int) game->m_maxMoney * 2.0, K_DISPLAY_SIZE_Y - 50),
                     glm::vec3(0.5, 0.5, 0.5));

  m_moneyBar2 = Triangle(&graphicsBackend.guiVBOdata,
                     &graphicsBackend.guicolorVBOdata,
                     glm::vec2(50, K_DISPLAY_SIZE_Y - 75),
                     glm::vec2(50 + (int) game->m_maxMoney * 2.0, K_DISPLAY_SIZE_Y - 75),
                     glm::vec2(50 + (int) game->m_maxMoney * 2.0, K_DISPLAY_SIZE_Y - 50),
                     glm::vec3(0.5, 0.5, 0.5));

  m_energyBar1 = Triangle(&graphicsBackend.guiVBOdata,
                     &graphicsBackend.guicolorVBOdata,
                     glm::vec2(50, K_DISPLAY_SIZE_Y - 50),
                     glm::vec2(50, K_DISPLAY_SIZE_Y - 75),
                     glm::vec2(50 + (int) game->m_curMoney * 2.0, K_DISPLAY_SIZE_Y - 50),
                     glm::vec3(1.0, 1.0, 1.0));

  m_energyBar2 = Triangle(&graphicsBackend.guiVBOdata,
                     &graphicsBackend.guicolorVBOdata,
                     glm::vec2(50, K_DISPLAY_SIZE_Y - 75),
                     glm::vec2(50 + (int) game->m_curMoney * 2.0, K_DISPLAY_SIZE_Y - 75),
                     glm::vec2(50 + (int) game->m_curMoney * 2.0, K_DISPLAY_SIZE_Y - 50),
                     glm::vec3(1.0, 1.0, 1.0));

}

GameLoop::~GameLoop() = default;

RenderLoop *GameLoop::update(Game *game) {
  auto penu = game->m_gameStateStack.end();

  for (auto key : game->m_keysDown) {
    switch (key) {
      case GLFW_KEY_V:
        penu--;
        penu--;

        game->m_gameStateTransition = TransitionLoop::makePopLoop(
            game, game->m_gameStateStack.back(), *penu);
        game->m_gameStateStack.pop_back();

        break;
    }
  }

  m_constructionManager->update(game);
  m_levelManager->update(game);

  game->m_entitySystem->update(game, false);


  m_moneyBar1.update(glm::vec2(50, K_DISPLAY_SIZE_Y - 50),
                 glm::vec2(50, K_DISPLAY_SIZE_Y - 75),
                 glm::vec2(50 + (int) game->m_maxMoney * 2.0, K_DISPLAY_SIZE_Y - 50),
                 glm::vec3(0.5, 0.5, 0.5));

  m_moneyBar2.update(glm::vec2(50, K_DISPLAY_SIZE_Y - 75),
                 glm::vec2(50 + (int) game->m_maxMoney * 2.0, K_DISPLAY_SIZE_Y - 75),
                 glm::vec2(50 + (int) game->m_maxMoney * 2.0, K_DISPLAY_SIZE_Y - 50),
                 glm::vec3(0.5, 0.5, 0.5));

  m_energyBar1.update(glm::vec2(50, K_DISPLAY_SIZE_Y - 50),
                 glm::vec2(50, K_DISPLAY_SIZE_Y - 75),
                 glm::vec2(50 + (int) game->m_curMoney * 2.0, K_DISPLAY_SIZE_Y - 50),
                 glm::vec3(1.0, 1.0, 1.0));

  m_energyBar2.update(glm::vec2(50, K_DISPLAY_SIZE_Y - 75),
                 glm::vec2(50 + (int) game->m_curMoney * 2.0, K_DISPLAY_SIZE_Y - 75),
                 glm::vec2(50 + (int) game->m_curMoney * 2.0, K_DISPLAY_SIZE_Y - 50),
                 glm::vec3(1.0, 1.0, 1.0));

  return this;
}

void GameLoop::render(Game *game) {
  game->m_entitySystem->m_graphics.update(game, game->m_entitySystem.get());

  m_constructionManager->render(game);
  m_levelManager->render(game);
}
