#pragma once
/**
 * TdGUIGraphicsSystem.hpp
 *
 * Victor Jiao
 *
 * Draws entities.
 */

#include "../TdGUIComponents/TdGUIGraphicsComponent.hpp"
#include "../TdGUIComponents/TdGUITextComponent.hpp"
#include <vector>

class TdGame;

class TdGUIGraphicsSystem {
public:
  std::vector<std::unique_ptr<TdGUITextComponent>> m_textComponents;
  std::vector<std::unique_ptr<TdGUIGraphicsComponent>> m_graphicsComponents;

  void update(TdGame *game) {
    for (auto &c : m_graphicsComponents) {
      c->update(game);
    }

    for (auto &c : m_textComponents) {
      c->update(game);
    }
  }
};
