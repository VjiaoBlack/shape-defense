#pragma once
/**
 * TdGUIClickableComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include "GUIComponent.hpp"
#include "GUIMouseComponent.hpp"

class GUIClickableComponent : public GUIComponent {
 public:
  bool m_pressedInside;
  bool m_releasedInside;
  bool m_wasPressed;
  bool m_activated;

  virtual void update(Game* game);
};

