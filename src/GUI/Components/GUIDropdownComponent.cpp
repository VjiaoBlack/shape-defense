/**
 * GUIDropdownComponent.cpp
 *
 * Victor Jiao
 *
 * Makes entities able to "appear" and "disappear"
 */


#include <GUI/Components/GUIDropdownComponent.hpp>
#include <GUI/GUIEntity.hpp>
#include <Game.hpp>

void GUIDropdownComponent::update(Game* game) {

//  if (!m_ent->has<GUIGraphicsComponent>() ||
//      !m_ent->has<GUIClickableComponent>()) {
//    LOG_FAT("NO GRAPHICS COMPONENT");
//    exit(1);
//    return;
//  }

  if (!m_button->get<GUIClickableComponent>()->m_activated) {
    return;
  }

  m_isOn = !m_isOn;

  if (!m_isOn) {
    for (auto b : m_ent->get<GUIContainerComponent>()->m_buttons) {
      b->get<GUIGraphicsComponent>()->destroy();
    }
  } else {
    for (auto b : m_ent->get<GUIContainerComponent>()->m_buttons) {
      b->get<GUIGraphicsComponent>()->refresh();
    }
  }
}
