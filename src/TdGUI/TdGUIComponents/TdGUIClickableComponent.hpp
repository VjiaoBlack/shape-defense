#pragma once
/**
 * TdGUIClickableComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include "TdGUIComponent.hpp"
#include "TdGUIMouseComponent.hpp"

class TdGUIClickableComponent : public TdGUIComponent {
 public:
  bool m_pressedInside;
  bool m_releasedInside;
  bool m_wasPressed;
  bool m_activated;

  virtual void update(TdGame* game);
};

