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
  std::unique_ptr<GUIEntity> m_button;

  virtual void update(Game* game) {
    // TODO
  }
};

