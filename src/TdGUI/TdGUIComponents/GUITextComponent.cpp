/**
 * TdGUITextComponent.cpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include <TdGUI/TdGUIComponents/GUITextComponent.hpp>
#include <Game.hpp>

GUITextComponent::GUITextComponent(Game *game, std::string label,
                                       MY_Rect r)
    : m_text(label), m_destRect(r) {
  m_textColor.a = 0xFF;
  m_textColor.r = 0x00;
  m_textColor.g = 0xFF;
  m_textColor.b = 0x00;

//  sdl_surface_pt textSurface(
//      TTF_RenderText_Solid(game->m_menuFont.get(), label.c_str(), m_textColor));

//  m_destRect.w = textSurface->w;
//  m_destRect.h = textSurface->h;
  m_destRect.x = r.x + (r.w - m_destRect.w) / 2;
  m_destRect.y = r.y + (r.h - m_destRect.h) / 2;

//  m_textTexture.reset(
//      SDL_CreateTextureFromSurface(game->m_SDLRenderer, textSurface.get()));
}

void GUITextComponent::update(Game *game) {
//  if (m_textTexture) {
//    SDL_RenderCopy(game->m_SDLRenderer, m_textTexture.get(), NULL, &m_destRect);
//  }
}
