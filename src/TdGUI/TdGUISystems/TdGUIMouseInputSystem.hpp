#pragma once
/**
 * TdGUIMouseInputSystem.hpp
 *
 * Victor Jiao
 *
 * Registers the changing mouse states of a system
 */

#include <vector>

#include "../TdGUIComponents/TdGUIClickableComponent.hpp"
#include "../TdGUIComponents/TdGUIMouseComponent.hpp"

class TdGUIMouseInputSystem {
public:
  std::vector<std::unique_ptr<TdGUIMouseComponent>> m_mouseComponents;
  std::vector<std::unique_ptr<TdGUIClickableComponent>> m_clickableComponents;

  void update(TdGame *game) {
    for (auto &c : m_mouseComponents) {
      c->update(game);
    }

    for (auto &c : m_clickableComponents) {
      c->update(game);
    }
  }
};
