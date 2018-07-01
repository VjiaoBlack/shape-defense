/**
 * TdGUIHighlightComponent.cpp
 *
 * Victor Jiao
 *
 * Enables components to have highlights
 */

#include <TdGUI/TdGUIComponents/TdGUIHighlightComponent.hpp>
#include <TdGUI/TdGUIEntity.hpp>

void TdGUIHighlightComponent::update(TdGame *game) {
  if (m_ent->get<TdGUIMouseComponent>()->m_mouseInside) {
    m_ent->get<TdGUIGraphicsComponent>()->m_drawColor = m_highlightColor;

  } else {
    m_ent->get<TdGUIGraphicsComponent>()->m_drawColor =
        m_ent->get<TdGUIGraphicsComponent>()->m_buttonColor;
  }
}

