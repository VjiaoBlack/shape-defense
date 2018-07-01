/**
 * TdGUIClickableComponent.cpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include <TdGUI/TdGUIComponents/TdGUIClickableComponent.hpp>
#include <TdGame.hpp>
#include <TdGUI/TdGUIEntity.hpp>

void TdGUIClickableComponent::update(TdGame* game) {
  if (m_releasedInside) {
    m_pressedInside = false;
    m_releasedInside = false;
    m_activated = false;
  }

  SDL_Point mousePos = {game->m_mouseX, game->m_mouseY};

  if (m_ent->get<TdGUIMouseComponent>()->m_mouseInside) {
    if (game->m_buttonsDown.count(SDL_BUTTON_LEFT)) {
      if (!m_wasPressed) {
        m_pressedInside = true;
      }
    } else if (m_pressedInside) {
      m_releasedInside = true;
      m_activated = true;
    }
  } else {
    m_pressedInside = false;
    m_releasedInside = false;
    m_activated = false;
  }

  m_wasPressed = game->m_buttonsDown.count(SDL_BUTTON_LEFT) != 0;
}

