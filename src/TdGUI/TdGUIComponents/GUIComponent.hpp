#pragma once
/**
 * TdGUIComponent.hpp
 *
 * Victor Jiao
 *
 * The abstract base class
 */

#include <memory>

class GUIEntity;
class Game;

class GUIComponent {
 public:
  GUIEntity* m_ent;
  virtual void update(Game* game) {};
};

