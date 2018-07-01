/**
 * TdGameLoop.cpp
 */

#include "TdECS/TdECSEntity.hpp"
#include "TdGameLoop.hpp"
#include "TdMainMenuLoop.hpp"
#include "TdTransitionLoop.hpp"

class TrMainMenuLoop;

TdGameLoop::TdGameLoop(TdGame *game) {
  m_rd = std::uniform_real_distribution<>(0.0, M_PI * 2);
}

TdGameLoop::~TdGameLoop() = default;

TdRenderLoop *TdGameLoop::update(TdGame *game) {
  auto penu = game->m_gameStateStack.end();
  for (auto key : game->m_keysDown) {
    switch (key) {
      case SDLK_v:
        penu--;
        penu--;

        game->m_gameStateTransition = TrTransitionLoop::makePopLoop(
            game, game->m_gameStateStack.back(), *penu);
        game->m_gameStateStack.pop_back();

        break;
      case SDLK_SPACE:
        double theta = m_rd(m_rg);
        double x = sin(theta) * 800 + K_DISPLAY_SIZE_X / 2.0;
        double y = cos(theta) * 800 + K_DISPLAY_SIZE_Y / 2.0;
        TdECSEntity::addEnemy(game, game->m_entitySystem.get(), x, y);
        break;
    }
  }

  game->m_entitySystem->m_planning.update(game);
  game->m_entitySystem->m_physics.update(game);
  return this;
}

void TdGameLoop::render(TdGame *game) {
  game->m_entitySystem->m_graphics.update(game);
}
