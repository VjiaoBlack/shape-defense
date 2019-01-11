#pragma once
/**
 * TdGUIGraphicsComponent.hpp
 *
 * Victor Jiao
 *
 * Enables components to be drawn (at all)
 */

#include <string>
#include "Graphics.hpp"
#include "GUIComponent.hpp"

class Game;

class GUIGraphicsComponent : public GUIComponent {
 public:
  MY_Rect m_rect;

  MY_Color m_buttonColor;

  MY_Color m_drawColor;

  GUIGraphicsComponent() = delete;

  GUIGraphicsComponent(MY_Rect rect) : m_rect(rect) {
    m_buttonColor = convertColorType(0xFF00FF00);

    m_drawColor = m_buttonColor;
  };

  virtual void update(Game *game);
};

