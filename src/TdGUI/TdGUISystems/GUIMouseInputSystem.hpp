#pragma once
/**
 * TdGUIMouseInputSystem.hpp
 *
 * Victor Jiao
 *
 * Registers the changing mouse states of a system
 */

#include <vector>

#include "TdGUI/TdGUIComponents/GUIClickableComponent.hpp"
#include "TdGUI/TdGUIComponents/GUIMouseComponent.hpp"

class GUIMouseInputSystem {
public:
  std::vector<std::unique_ptr<GUIMouseComponent>> m_mouseComponents;
  std::vector<std::unique_ptr<GUIClickableComponent>> m_clickableComponents;

  void update(Game *game) {
    for (auto &c : m_mouseComponents) {
      c->update(game);
    }

    for (auto &c : m_clickableComponents) {
      c->update(game);
    }
  }
};
