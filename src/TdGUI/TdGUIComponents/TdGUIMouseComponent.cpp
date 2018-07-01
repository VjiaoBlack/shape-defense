/**
 * TdGUIMouseComponent.cpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include <TdGUI/TdGUIComponents/TdGUIMouseComponent.hpp>
#include <TdGame.hpp>
#include <TdGUI/TdGUIEntity.hpp>

void TdGUIMouseComponent::update(TdGame* game) {
  SDL_Point mousePos = {game->m_mouseX, game->m_mouseY};

  if (SDL_PointInRect(&mousePos, &m_ent->get<TdGUIGraphicsComponent>()->m_rect)) {
    m_mouseInside = true;
  } else {
    m_mouseInside = false;
  }
}

