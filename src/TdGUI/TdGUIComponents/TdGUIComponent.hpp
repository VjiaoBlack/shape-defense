#pragma once
/**
 * TdGUIComponent.hpp
 *
 * Victor Jiao
 *
 * The abstract base class
 */

#include <memory>

class TdGUIEntity;
class TdGame;

class TdGUIComponent {
 public:
  TdGUIEntity* m_ent;
  virtual void update(TdGame* game) {};
};

