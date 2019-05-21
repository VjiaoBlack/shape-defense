#pragma once
/**
 * TdGUIMouseComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include "GUIComponent.hpp"
#include "GUIGraphicsComponent.hpp"

class GUIMouseComponent : public GUIComponent {
 public:
  bool m_mouseInside;

  virtual void update(Game* game);
};

