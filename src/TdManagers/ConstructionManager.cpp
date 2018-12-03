/**
 * TdConstructionManager.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "ConstructionManager.hpp"
#include "TdECS/Entity.hpp"
#include "Game.hpp"

void ConstructionManager::update(Game *game) {
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
      b.w  = 16;
      b.h  = 16;
      b.x += 16;
      b.y += 16;
      SDL_RenderDrawRect(game->m_SDLRenderer, &b);
    }
  }
}

// right now just builds a tower
void ConstructionManager::build(Game *game) {
  if (m_isOn) {
    if (m_isTower && game->m_curMoney >= 20.0) {
      Entity::addTower(game, game->m_entitySystem.get(),
                       m_rect.x / 16 - 50, m_rect.y / 16 - 28);
      game->m_curMoney -= 20.0;
    } else if (!m_isTower && game->m_curMoney >= 5.0) {
      Entity::addWall(game, game->m_entitySystem.get(),
                      m_rect.x / 16 - 49, m_rect.y / 16 - 27);
      game->m_curMoney -= 5.0;
    }
  }
}