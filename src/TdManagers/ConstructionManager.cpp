/**
 * TdConstructionManager.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "ConstructionManager.hpp"
#include "ECS/Entity.hpp"
#include "Game.hpp"

ConstructionManager::ConstructionManager(Game* game) {
  m_GUISystem = std::make_unique<GUISystem>();

  MY_Rect r =
      (MY_Rect){sz(K_DISPLAY_SIZE_X * 3 / 4),
                 sz(K_DISPLAY_SIZE_Y / 2 - K_DISPLAY_SIZE_Y / 4 - K_DISPLAY_SIZE_Y / 8),
                 sz(200), sz(K_DISPLAY_SIZE_Y * 3 / 4)};

  vector<string> labels = {"Toggle", "Tower", "Wall"};
  m_GUIMenu = GUIEntity::addVerticalMenu(game, m_GUISystem.get(), r,
                                         labels);

  m_GUIMenu->get<GUIContainerComponent>()->m_buttons[0]->get<GUIClickableComponent>()->setCallback(
      [&]() { m_isOn = !m_isOn; printf("TOGGLE, is now %d\n", (uint) m_isOn); });

  m_GUIMenu->get<GUIContainerComponent>()->m_buttons[1]->get<GUIClickableComponent>()->setCallback(
      [&]() { m_type = EntityType::TOWER; });

  m_GUIMenu->get<GUIContainerComponent>()->m_buttons[2]->get<GUIClickableComponent>()->setCallback(
      [&]() { m_type = EntityType::WALL; });

  r = (MY_Rect) {sz(K_DISPLAY_SIZE_X / 2) - 100,
                 sz(K_DISPLAY_SIZE_Y / 2) + 200,
                 sz(100),
                 sz(100)};

  m_GUIMoney = GUIEntity::addLabel(game,
                                   m_GUISystem.get(),
                                   r,
                                   "energy");

  r.x += 200;
  m_GUIBuilding = GUIEntity::addLabel(game,
                                      m_GUISystem.get(),
                                      r,
                                      "true");
}

void ConstructionManager::update(Game *game) {
  m_GUIMoney->get<GUITextComponent>()->m_text    = std::to_string((int)game->m_curMoney) + "/" +
                                                   std::to_string((int)game->m_maxMoney);
  m_GUIBuilding->get<GUITextComponent>()->m_text = std::to_string(m_isOn);

  // update building menu (also draws)
  m_GUISystem->update(game);

  for (auto button : game->m_buttonsDown) {
    switch (button) {
      case GLFW_MOUSE_BUTTON_LEFT:
        if (!game->m_buttonsDownPrev.count(GLFW_MOUSE_BUTTON_LEFT)) {
          build(game);
        }
        break;
    }
  }
}

void ConstructionManager::render(Game* game) {
  // render building menu
  m_GUISystem->m_graphics.update(game);

  // render the "future object"
  if (m_isOn) {
    // not totally trivial due to integer division's trucation
    m_rect.x = (1 + ((int)game->m_mouseX - 16) / 16) * 16;
    m_rect.y = (1 + ((int)game->m_mouseY - 16) / 16) * 16;

    MY_Rect b = m_rect;

    switch (m_type) {
      case EntityType::TOWER:
        break;
      case EntityType::WALL:
        b.w  = 16;
        b.h  = 16;
        break;
      default:
        LOG_ERR("Construction manager has unhandled entity type: %d", (uint) m_type);
        break;
    }
  }
}

// right now just builds a tower
void ConstructionManager::build(Game *game) {
  printf("%f\n", game->m_curMoney);
  if (m_isOn && game->m_curMoney >= EntityCosts[(uint)m_type]) {
    if (!m_GUIMenu->get<GUIContainerComponent>()->m_buttons[0]
          ->get<GUIClickableComponent>()->m_pressedInside &&
        !m_GUIMenu->get<GUIContainerComponent>()->m_buttons[1]
          ->get<GUIClickableComponent>()->m_pressedInside &&
        !m_GUIMenu->get<GUIContainerComponent>()->m_buttons[2]
          ->get<GUIClickableComponent>()->m_pressedInside) {

      LOG_INF("Grid %d, %d\n", m_rect.x / 16, m_rect.y / 16);
      Entity::addEntity(game,
                        game->m_entitySystem.get(),
                        m_type,
                        m_rect.x / 16,
                        m_rect.y / 16);
      game->m_curMoney -= EntityCosts[(uint) m_type];
    }
  }
}