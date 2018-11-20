#pragma once
/**
 * TdGUIGraphicsSystem.hpp
 *
 * Victor Jiao
 *
 * Draws entities.
 */

#include "TdGUI/TdGUIComponents/GUIGraphicsComponent.hpp"
#include "TdGUI/TdGUIComponents/GUITextComponent.hpp"
#include <vector>

class Game;

class GUIGraphicsSystem {
public:
  std::vector<std::unique_ptr<GUITextComponent>> m_textComponents;
  std::vector<std::unique_ptr<GUIGraphicsComponent>> m_graphicsComponents;

  void update(Game *game) {
    for (auto &c : m_graphicsComponents) {
      c->update(game);
    }

    for (auto &c : m_textComponents) {
      c->update(game);
    }
  }
};
