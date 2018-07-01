#pragma once
/**
 * TdGUIContainerComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities able to have things inside it
 */

#include "TdGUIComponent.hpp"
#include <vector>

class TdGUIEntity;

class TdGUIContainerComponent : public TdGUIComponent {
public:
  int m_spacing = 10;
  std::vector<TdGUIEntity *> m_buttons;

  TdGUIContainerComponent() {}
  virtual void update(TdGame *game){};
};
