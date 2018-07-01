#pragma once
/**
 * TdGUIMouseComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include "TdGUIComponent.hpp"
#include "TdGUIGraphicsComponent.hpp"

class TdGUIMouseComponent : public TdGUIComponent {
 public:
  bool m_mouseInside;

  virtual void update(TdGame* game);
};

