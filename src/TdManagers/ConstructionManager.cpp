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

ConstructionManager::ConstructionManager(Game* game) {
  m_GUISystem = std::make_unique<GUISystem>();

  SDL_Rect r =
      (SDL_Rect){sz(K_DISPLAY_SIZE_X * 3 / 4),
                 sz(K_DISPLAY_SIZE_Y / 2 - K_DISPLAY_SIZE_Y / 4 - K_DISPLAY_SIZE_Y / 8),
                 sz(200), sz(K_DISPLAY_SIZE_Y * 3 / 4)};

  vector<string> labels = {"Toggle", "Tower", "Wall"};
  m_GUIMenu = GUIEntity::addVerticalMenu(game, m_GUISystem.get(), r,
                                         labels);
}

void ConstructionManager::update(Game *game) {
  for (auto button : game->m_buttonsDown) {
    switch (button) {
      case SDL_BUTTON_LEFT:
        if (!game->m_buttonsDownPrev.count(SDL_BUTTON_LEFT)) {
          build(game);
        }
        break;
    }
  }

  if (m_GUIMenu->get<GUIContainerComponent>()
      ->m_buttons[0]
      ->get<GUIClickableComponent>()
      ->m_activated) {
    m_isOn = !m_isOn;
  }

  if (m_GUIMenu->get<GUIContainerComponent>()
      ->m_buttons[1]
      ->get<GUIClickableComponent>()
      ->m_activated) {
    m_type = EntityType::TOWER;
  }


  if (m_GUIMenu->get<GUIContainerComponent>()
      ->m_buttons[2]
      ->get<GUIClickableComponent>()
      ->m_activated) {
    m_type = EntityType::WALL;
  }
}

void ConstructionManager::render(Game* game) {
  // render building menu
  m_GUISystem->update(game);

  // render the "future object"
  if (m_isOn) {
    // not totally trivial due to integer division's trucation
    m_rect.x = (1 + (game->m_mouseX - 16) / 16) * 16 + 0;
    m_rect.y = (1 + (game->m_mouseY - 16) / 16) * 16 + 2;

    SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect b = m_rect;

    switch (m_type) {
      case EntityType::TOWER:
        SDL_RenderDrawRect(game->m_SDLRenderer, &m_rect);
        break;
      case EntityType::WALL:
        b.w  = 16;
        b.h  = 16;
        SDL_RenderDrawRect(game->m_SDLRenderer, &b);
        break;
      default:
        LOG_ERR("Construction manager has unhandled entity type: %d", (uint) m_type);
        break;
    }
  }
}

// right now just builds a tower
void ConstructionManager::build(Game *game) {
  if (m_isOn && game->m_curMoney >= EntityCosts[(uint)m_type]) {
    Entity::addEntity(game, game->m_entitySystem.get(), m_type, m_rect.x / 16 - 50, m_rect.y / 16 - 28);
    game->m_curMoney -= EntityCosts[(uint)m_type];
  }
}