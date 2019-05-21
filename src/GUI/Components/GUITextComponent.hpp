#pragma once
/**
 * TdGUITextComponent.hpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include "GUIComponent.hpp"
#include "GUIGraphicsComponent.hpp"

class GUITextComponent : public GUIComponent {
 public:
  std::string m_text;
//  sdl_texture_pt m_textTexture;
  MY_Rect m_destRect;
  MY_Color m_textColor;

  GUITextComponent(Game* game, std::string label, MY_Rect r);

  virtual void update(Game* game);
};

