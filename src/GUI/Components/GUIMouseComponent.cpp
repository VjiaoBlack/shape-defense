/**
 * TdGUIMouseComponent.cpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include <GUI/Components/GUIMouseComponent.hpp>
#include <Game.hpp>
#include <GUI/GUIEntity.hpp>

void GUIMouseComponent::update(Game* game) {
  if (Game::m_mouseX >= m_ent->get<GUIGraphicsComponent>()->m_rect.x &&
      Game::m_mouseX <= m_ent->get<GUIGraphicsComponent>()->m_rect.x +
                        m_ent->get<GUIGraphicsComponent>()->m_rect.w &&
      Game::m_mouseY >= m_ent->get<GUIGraphicsComponent>()->m_rect.y &&
      Game::m_mouseY <= m_ent->get<GUIGraphicsComponent>()->m_rect.y +
                        m_ent->get<GUIGraphicsComponent>()->m_rect.h) {
    m_mouseInside = true;
  } else {
    m_mouseInside = false;
  }
}

