#pragma once
/**
 * TdGUIGraphicsComponent.hpp
 *
 * Victor Jiao
 *
 * Enables components to be drawn (at all)
 */

#include <string>
#include "../../TrGraphics.hpp"
#include "TdGUIComponent.hpp"

class TdGame;

class TdGUIGraphicsComponent : public TdGUIComponent {
 public:
  SDL_Rect m_rect;

  SDL_Color m_buttonColor;

  SDL_Color m_drawColor;

  TdGUIGraphicsComponent() = delete;

  TdGUIGraphicsComponent(SDL_Rect rect) : m_rect(rect) {
    m_buttonColor = convertColorType(0xFF00FF00);

    m_drawColor = m_buttonColor;
  };

  virtual void update(TdGame *game);
};

