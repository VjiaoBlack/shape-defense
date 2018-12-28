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
  for (auto key : game->m_keysDown) {
    switch (key) {
      case SDLK_b:
        if (!game->m_keysDownPrev.count(SDLK_b)) {
          m_isOn = !m_isOn;
          if (m_isOn) {
            LOG_INF("BUILDING MODE ON");
            m_isOn = true;
          } else {
            LOG_INF("building mode off");
            m_isOn = false;
          }
        }
        break;
      case SDLK_1:
        if (!game->m_keysDownPrev.count(SDLK_1) && m_isOn) {
          LOG_INF("WALL MODE ON");
          m_isTower = false;
          m_type    = EntityType::WALL;
        }
        break;
      case SDLK_2:
        if (!game->m_keysDownPrev.count(SDLK_2) && m_isOn) {
          LOG_INF("wall mode off");
          m_isTower = true;
          m_type    = EntityType::TOWER;
        }
        break;
    }
  }

  for (auto button : game->m_buttonsDown) {
    switch (button) {
      case SDL_BUTTON_LEFT:
        if (!game->m_buttonsDownPrev.count(SDL_BUTTON_LEFT)) {
          build(game);
        }
        break;
    }
  }

  // render the "future object"
  if (m_isOn) {
    // not totally trivial due to integer division's trucation
    m_rect.x = (1 + (game->m_mouseX - 16) / 16) * 16 + 0;
    m_rect.y = (1 + (game->m_mouseY - 16) / 16) * 16 + 2;

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
    Entity::addEntity(game, game->m_entitySystem.get(), m_type, m_rect.x / 16 - 50, m_rect.y / 16 - 28);
  }
}