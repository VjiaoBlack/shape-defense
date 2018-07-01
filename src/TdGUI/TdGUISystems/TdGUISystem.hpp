#pragma once

/**
 * TdGUISystem.hpp
 *
 * Victor Jiao
 *
 * Handles a GUI System.
 */

#include <TdGUI/TdGUIComponents/TdGUIContainerComponent.hpp>
#include <list>

#include "TdGUIGraphicsSystem.hpp"
#include "TdGUIMouseInputSystem.hpp"
#include "TdGUIResponsiveSystem.hpp"

class TdGUIClickableComponent;
class TdGUIDropdownComponent;
class TdGUIMouseComponent;

class TdGUISystem {
public:
  TdGUIGraphicsSystem m_graphics;
  TdGUIMouseInputSystem m_mouse;
  TdGUIResponsiveSystem m_response;

  std::vector<std::unique_ptr<TdGUIContainerComponent>> m_containerComponents;

  std::list<std::unique_ptr<TdGUIEntity>> m_entities;

  void update(TdGame *game) {
    m_mouse.update(game);
    m_response.update(game);
    m_graphics.update(game);
  }

  void addComponent(std::unique_ptr<TdGUIClickableComponent> c) {
    m_mouse.m_clickableComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdGUIDropdownComponent> c) {
    m_response.m_dropdownComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdGUIGraphicsComponent> c) {
    m_graphics.m_graphicsComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdGUIHighlightComponent> c) {
    m_response.m_highlightComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdGUIMouseComponent> c) {
    m_mouse.m_mouseComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdGUITextComponent> c) {
    m_graphics.m_textComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdGUIContainerComponent> c) {
    m_containerComponents.push_back(std::move(c));
  }
};
