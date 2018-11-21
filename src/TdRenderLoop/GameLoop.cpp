/**
 * TdGameLoop.cpp
 */

#include "GameLoop.hpp"
#include "TdManagers/ConstructionManager.hpp"
#include "TdECS/Entity.hpp"
#include "MainMenuLoop.hpp"
#include "TransitionLoop.hpp"

class MainMenuLoop;

void GameLoop::addRandomEnemy(Game *game, double dist) {
  double theta = m_rd(m_rg);
  double x = sin(theta) * dist + K_DISPLAY_SIZE_X / 2.0;
  double y = cos(theta) * dist + K_DISPLAY_SIZE_Y / 2.0;
  Entity::addEnemy(game, game->m_entitySystem.get(), x, y);
}

GameLoop::GameLoop(Game *game) {
  m_rd = std::uniform_real_distribution<>(0.0, M_PI * 2);

  this->addRandomEnemy(game, 300);
  this->addRandomEnemy(game, 400);
  this->addRandomEnemy(game, 500);
  this->addRandomEnemy(game, 600);

  m_constructionManager = std::make_unique<ConstructionManager>();
}

GameLoop::~GameLoop() = default;

RenderLoop *GameLoop::update(Game *game) {
  auto penu = game->m_gameStateStack.end();
  for (auto key : game->m_keysDown) {
    switch (key) {
      case SDLK_v:
        penu--;
        penu--;

        game->m_gameStateTransition = TransitionLoop::makePopLoop(
            game, game->m_gameStateStack.back(), *penu);
        game->m_gameStateStack.pop_back();

        break;
      case SDLK_SPACE:
        this->addRandomEnemy(game, 1000);
        break;
      case SDLK_b:
        if (!game->m_keysDownPrev.count(SDLK_b)) {
          m_isBuilding = !m_isBuilding;
          if (m_isBuilding) {
            LOG_INF("BUILDING MODE ON");
            m_constructionManager->m_isOn = true;
          } else {
            LOG_INF("building mode off");
            m_constructionManager->m_isOn = false;
          }
        }
        break;
      case SDLK_n:
        if (!game->m_keysDownPrev.count(SDLK_n)) {
          if (m_constructionManager->m_isTower) {
            LOG_INF("WALL MODE ON");
            m_constructionManager->m_isTower = false;
          } else {
            LOG_INF("wall mode off");
            m_constructionManager->m_isTower = true;
          }
        }
        break;
    }
  }

  for (auto button : game->m_buttonsDown) {
    switch (button) {
      case SDL_BUTTON_LEFT:
        if (!game->m_buttonsDownPrev.count(SDL_BUTTON_LEFT)) {
          m_constructionManager->build(game);
        }
        break;
    }
  }

  game->m_entitySystem->update(game, false);

  m_constructionManager->update(game);

  if (m_enemySpawnTimer == 15) {
    this->addRandomEnemy(game, 1000);
    m_enemySpawnTimer = 0;
  }

  m_enemySpawnTimer++;

  return this;
}

void GameLoop::render(Game *game) {
  // set scale for rendering debug
//  SDL_RenderSetScale(game->m_SDLRenderer, 2.0, 2.0);

  // game->m_entitySystem->m_graphics.update(game);

  // draw grid
  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0x10, 0x20, 0x10, 0xFF);

  // vertical lines
  int posx = 0;
  while (posx <= K_DISPLAY_SIZE_X / 2) {
    SDL_RenderDrawLine(game->m_SDLRenderer, K_DISPLAY_SIZE_X / 2 + posx, 0,
                       K_DISPLAY_SIZE_X / 2 + posx, K_DISPLAY_SIZE_Y);
    SDL_RenderDrawLine(game->m_SDLRenderer, -1 + K_DISPLAY_SIZE_X / 2 + posx, 0,
                       -1 + K_DISPLAY_SIZE_X / 2 + posx, K_DISPLAY_SIZE_Y);

    SDL_RenderDrawLine(game->m_SDLRenderer, K_DISPLAY_SIZE_X / 2 - posx, 0,
                       K_DISPLAY_SIZE_X / 2 - posx, K_DISPLAY_SIZE_Y);
    SDL_RenderDrawLine(game->m_SDLRenderer, -1 + K_DISPLAY_SIZE_X / 2 - posx, 0,
                       -1 + K_DISPLAY_SIZE_X / 2 - posx, K_DISPLAY_SIZE_Y);
    posx += 16;
  }

  // horizontal lines
  int posy = 0;
  while (posy <= K_DISPLAY_SIZE_Y / 2) {
    SDL_RenderDrawLine(game->m_SDLRenderer, 0, K_DISPLAY_SIZE_Y / 2 + posy,
                       K_DISPLAY_SIZE_X, K_DISPLAY_SIZE_Y / 2 + posy);
    SDL_RenderDrawLine(game->m_SDLRenderer, 0, -1 + K_DISPLAY_SIZE_Y / 2 + posy,
                       K_DISPLAY_SIZE_X, -1 + K_DISPLAY_SIZE_Y / 2 + posy);

    SDL_RenderDrawLine(game->m_SDLRenderer, 0, K_DISPLAY_SIZE_Y / 2 - posy,
                       K_DISPLAY_SIZE_X, K_DISPLAY_SIZE_Y / 2 - posy);
    SDL_RenderDrawLine(game->m_SDLRenderer, 0, -1 + K_DISPLAY_SIZE_Y / 2 - posy,
                       K_DISPLAY_SIZE_X, -1 + K_DISPLAY_SIZE_Y / 2 - posy);
    posy += 16;
  }

  game->m_entitySystem->m_graphics.update(game, game->m_entitySystem.get());
}
