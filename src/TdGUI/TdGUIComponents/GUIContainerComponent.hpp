#pragma once
/**
 * TdGUIContainerComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities able to have things inside it
 */

#include "GUIComponent.hpp"
#include <vector>

class GUIEntity;

class GUIContainerComponent : public GUIComponent {
public:
  int m_spacing = 10;
  std::vector<GUIEntity *> m_buttons;

  GUIContainerComponent() {}
  virtual void update(Game *game){};
};
