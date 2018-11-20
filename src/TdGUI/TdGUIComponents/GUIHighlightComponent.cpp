/**
 * TdGUIHighlightComponent.cpp
 *
 * Victor Jiao
 *
 * Enables components to have highlights
 */

#include <TdGUI/TdGUIComponents/GUIHighlightComponent.hpp>
#include <TdGUI/GUIEntity.hpp>

void GUIHighlightComponent::update(Game *game) {
  if (m_ent->get<GUIMouseComponent>()->m_mouseInside) {
    m_ent->get<GUIGraphicsComponent>()->m_drawColor = m_highlightColor;

  } else {
    m_ent->get<GUIGraphicsComponent>()->m_drawColor =
        m_ent->get<GUIGraphicsComponent>()->m_buttonColor;
  }
}

