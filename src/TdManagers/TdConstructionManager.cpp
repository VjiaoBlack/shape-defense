/**
 * TdConstructionManager.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdConstructionManager.hpp"
#include "../TdECS/TdECSEntity.hpp"
#include "../TdGame.hpp"

void TdConstructionManager::update(TdGame* game) {
  if (m_isOn) {
    m_rect.x = game->m_mouseX - 16;
    m_rect.y = game->m_mouseY - 16;

    m_rect.x = (m_rect.x / 16) * 16 + 0;
    m_rect.y = (m_rect.y / 16) * 16 + 2;

    SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if (m_isTower) {
      SDL_RenderDrawRect(game->m_SDLRenderer, &m_rect);

    } else {
      SDL_Rect b = m_rect;
      b.w = 16;
      b.h = 16;
      b.x += 16;
      b.y += 16;
      SDL_RenderDrawRect(game->m_SDLRenderer, &b);
    }
  }
}

// right now just builds a tower
void TdConstructionManager::build(TdGame* game) {
  if (m_isOn) {
    if (m_isTower) {
      TdECSEntity::addTower(game, game->m_entitySystem.get(),
                            m_rect.x / 16 - 50, m_rect.y / 16 - 28);
    } else {
      TdECSEntity::addWall(game, game->m_entitySystem.get(),
                            m_rect.x / 16 - 49, m_rect.y / 16 - 27);
    }
  }
}