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

    m_rect.x = (1 + m_rect.x / 16) * 16 + 0;
    m_rect.y = (1 + m_rect.y / 16) * 16 + 2;

    SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if (m_isTower) {
      SDL_RenderDrawRect(game->m_SDLRenderer, &m_rect);
    } else {
      SDL_Rect b = m_rect;
      b.w  = 16;
      b.h  = 16;
      SDL_RenderDrawRect(game->m_SDLRenderer, &b);
    }
  }
}

// right now just builds a tower
void ConstructionManager::build(Game *game) {
  if (m_isOn) {
//    switch (m_type) {
//      case EntityType::WALL:
//        break;
//      case EntityType::TOWER:
//        break;
//    }

    if (m_isTower && game->m_curMoney >= 20.0) {
      Entity::addEntity<EntityType::TOWER>(game, game->m_entitySystem.get(),
                       m_rect.x / 16 - 50, m_rect.y / 16 - 28);
      game->m_curMoney -= 20.0;
    } else if (!m_isTower && game->m_curMoney >= 5.0) {
      Entity::addEntity<EntityType::WALL>(game, game->m_entitySystem.get(),
                      m_rect.x / 16 - 50, m_rect.y / 16 - 28);
      game->m_curMoney -= 5.0;
    }
  }
}