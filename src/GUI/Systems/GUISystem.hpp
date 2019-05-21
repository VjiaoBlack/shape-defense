#pragma once

/**
 * TdGUISystem.hpp
 *
 * Victor Jiao
 *
 * Handles a GUI System.
 */

#include <GUI/Components/GUIContainerComponent.hpp>
#include <list>

#include "GUIGraphicsSystem.hpp"
#include "GUIMouseInputSystem.hpp"
#include "GUIResponsiveSystem.hpp"

class GUIClickableComponent;
class GUIDropdownComponent;
class GUIMouseComponent;

class GUISystem {
public:
  GUIGraphicsSystem m_graphics;
  GUIMouseInputSystem m_mouse;
  GUIResponsiveSystem m_response;

  std::vector<std::unique_ptr<GUIContainerComponent>> m_containerComponents;

  std::list<std::unique_ptr<GUIEntity>> m_entities;

  void update(Game *game) {
    m_mouse.update(game);
    m_response.update(game);
    m_graphics.update(game);
  }

  void addComponent(std::unique_ptr<GUIClickableComponent> c) {
    m_mouse.m_clickableComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<GUIDropdownComponent> c) {
    m_response.m_dropdownComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<GUIGraphicsComponent> c) {
    m_graphics.m_graphicsComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<GUIHighlightComponent> c) {
    m_response.m_highlightComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<GUIMouseComponent> c) {
    m_mouse.m_mouseComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<GUITextComponent> c) {
    m_graphics.m_textComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<GUIContainerComponent> c) {
    m_containerComponents.push_back(std::move(c));
  }
};
