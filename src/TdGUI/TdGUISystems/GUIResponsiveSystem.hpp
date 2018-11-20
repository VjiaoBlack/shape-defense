#pragma once
/**
 * TdGUIResponsiveSystem.hpp
 *
 * Victor Jiao
 *
 * Updates entities responses - highlights, activations, drop-downs, etc.
 */

#include <vector>

#include "TdGUI/TdGUIComponents/GUIDropdownComponent.hpp"
#include "TdGUI/TdGUIComponents/GUIHighlightComponent.hpp"

class GUIResponsiveSystem {
public:
  std::vector<std::unique_ptr<GUIHighlightComponent>> m_highlightComponents;
  std::vector<std::unique_ptr<GUIDropdownComponent>> m_dropdownComponents;

  void update(Game *game) {
    for (auto &c : m_highlightComponents) {
      c->update(game);
    }

    for (auto &c : m_dropdownComponents) {
      c->update(game);
    }
  }
};
