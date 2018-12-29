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

GameLoop::GameLoop(Game *game) {
  m_constructionManager = std::make_unique<ConstructionManager>(game);
  m_levelManager = std::make_unique<LevelManager>(game);
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
    }
  }

  m_constructionManager->update(game);
  m_levelManager->update(game);

  game->m_entitySystem->update(game, false);

  return this;
}

void GameLoop::render(Game *game) {
  // set scale for rendering debug
//  SDL_RenderSetScale(game->m_SDLRenderer, 2.0, 2.0);

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

  // draw money
  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0x80);
  SDL_RenderDrawLine(game->m_SDLRenderer, 50, 50, 50 + (int) game->m_maxMoney * 2.0, 50);

  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0x80, 0x80, 0xFF, 0x80);
  SDL_RenderDrawLine(game->m_SDLRenderer, 50, 75, 50 + (int) game->m_maxEnergy * 2.0, 75);

  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderDrawLine(game->m_SDLRenderer, 50, 50, 50 + (int) game->m_curMoney * 2.0, 50);

  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0x80, 0x80, 0xFF, 0xFF);
  SDL_RenderDrawLine(game->m_SDLRenderer, 50, 75, 50 + (int) game->m_curEnergy * 2.0, 75);

  m_constructionManager->render(game);
  m_levelManager->render(game);
}
