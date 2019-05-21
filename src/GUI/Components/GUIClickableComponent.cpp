/**
 * TdGUIClickableComponent.cpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include <GUI/Components/GUIClickableComponent.hpp>
#include <Game.hpp>
#include <GUI/GUIEntity.hpp>

void GUIClickableComponent::update(Game* game) {
  if (m_releasedInside) {
    m_pressedInside = false;
    m_releasedInside = false;
    m_activated = false;
  }

  if (m_ent->get<GUIMouseComponent>()->m_mouseInside) {
    if (game->m_buttonsDown.count(GLFW_MOUSE_BUTTON_LEFT)) {
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

  m_wasPressed = game->m_buttonsDown.count(GLFW_MOUSE_BUTTON_LEFT) != 0;

  if (m_activated && m_hasCallback) {
    m_callback();
  }
}

void GUIClickableComponent::setCallback(std::function<void()> callback) {
  m_hasCallback = true;
  m_callback    = callback;
}

