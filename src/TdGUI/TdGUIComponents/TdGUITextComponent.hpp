#pragma once
/**
 * TdGUITextComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include "TdGUIComponent.hpp"
#include "TdGUIGraphicsComponent.hpp"

class TdGUITextComponent : public TdGUIComponent {
 public:
  std::string m_text;
  sdl_texture_pt m_textTexture;
  SDL_Rect m_destRect;
  SDL_Color m_textColor;

  TdGUITextComponent(TdGame* game, std::string &&label, SDL_Rect r);

  virtual void update(TdGame* game);
};

