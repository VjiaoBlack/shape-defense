#pragma once
/**
 * TdGUIResponsiveSystem.hpp
 *
 * Victor Jiao
 *
 * Updates entities responses - highlights, activations, drop-downs, etc.
 */

#include <vector>

#include "../TdGUIComponents/TdGUIDropdownComponent.hpp"
#include "../TdGUIComponents/TdGUIHighlightComponent.hpp"

class TdGUIResponsiveSystem {
public:
  std::vector<std::unique_ptr<TdGUIHighlightComponent>> m_highlightComponents;
  std::vector<std::unique_ptr<TdGUIDropdownComponent>> m_dropdownComponents;

  void update(TdGame *game) {
    for (auto &c : m_highlightComponents) {
      c->update(game);
    }

    for (auto &c : m_dropdownComponents) {
      c->update(game);
    }
  }
};
