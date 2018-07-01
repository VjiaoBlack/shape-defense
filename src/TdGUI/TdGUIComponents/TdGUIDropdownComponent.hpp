#pragma once
/**
 * TdGUIDropdownComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities able to "appear" and "disappear"
 */

#include "TdGUIComponent.hpp"
#include <memory>

class TdGUIDropdownComponent : public TdGUIComponent {
// only activates when another TdGUIEntity is clicked
 public:
  std::unique_ptr<TdGUIEntity> m_button;

  virtual void update(TdGame* game) {
    // TODO
  }
};

