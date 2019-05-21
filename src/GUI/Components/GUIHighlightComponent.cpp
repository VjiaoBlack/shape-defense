/**
 * TdGUIHighlightComponent.cpp
 *
 * Victor Jiao
 *
 * Enables components to have highlights
 */

#include <GUI/Components/GUIHighlightComponent.hpp>
#include <GUI/GUIEntity.hpp>

void GUIHighlightComponent::update(Game *game) {
  if (m_ent->get<GUIMouseComponent>()->m_mouseInside) {
    if (m_ent->get<GUIClickableComponent>()->m_pressedInside) {
      m_ent->get<GUIGraphicsComponent>()->m_rect1.update(
          glm::vec3(0.5, 0.5, 0.5));
      m_ent->get<GUIGraphicsComponent>()->m_rect2.update(
          glm::vec3(0.5, 0.5, 0.5));
    } else {
      m_ent->get<GUIGraphicsComponent>()->m_rect1.update(
          glm::vec3(m_highlightColor.r, m_highlightColor.g, m_highlightColor.b));
      m_ent->get<GUIGraphicsComponent>()->m_rect2.update(
          glm::vec3(m_highlightColor.r, m_highlightColor.g, m_highlightColor.b));
    }
  } else {
    glm::vec3 color = glm::vec3(
      m_ent->get<GUIGraphicsComponent>()->m_buttonColor.r,
      m_ent->get<GUIGraphicsComponent>()->m_buttonColor.g,
      m_ent->get<GUIGraphicsComponent>()->m_buttonColor.b);
    m_ent->get<GUIGraphicsComponent>()->m_rect1.update(color);
    m_ent->get<GUIGraphicsComponent>()->m_rect2.update(color);
  }
}

