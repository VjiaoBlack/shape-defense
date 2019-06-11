#pragma once
/**
 * TdGUIDropdownComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities able to "appear" and "disappear"
 */

#include "GUIComponent.hpp"
#include <memory>

class GUIDropdownComponent : public GUIComponent {
// only activates when another GUIEntity is clicked
 public:
  bool m_isOn = true;
  GUIEntity* m_button{};

  GUIDropdownComponent() = delete;
  GUIDropdownComponent(GUIEntity* button) : m_button(button) {};


  virtual void update(Game* game);
};

