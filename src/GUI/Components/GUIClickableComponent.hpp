#pragma once
/**
 * TdGUIClickableComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include <functional>
#include "GUIComponent.hpp"
#include "GUIMouseComponent.hpp"

class GUIClickableComponent : public GUIComponent {
 public:
  std::function<void()> m_callback;
  bool m_hasCallback;

  bool m_pressedInside;
  bool m_releasedInside;
  bool m_wasPressed;
  bool m_activated;

  virtual void update(Game* game);

  void setCallback(std::function<void()> callback);
};

