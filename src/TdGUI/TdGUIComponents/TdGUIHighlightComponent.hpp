#pragma once
/**
 * TdGUIHighlightComponent.hpp
 *
 * Victor Jiao
 *
 * Enables components to have highlights
 */

#include "TdGUIComponent.hpp"
#include "TdGUIMouseComponent.hpp"
#include <memory>

class TdGUIHighlightComponent : public TdGUIComponent {
 public:
  SDL_Color m_highlightColor;

  TdGUIHighlightComponent() {
    m_highlightColor.r = 0xFF;
    m_highlightColor.g = 0xFF;
    m_highlightColor.b = 0x80;
    m_highlightColor.a = 0x80;
  };

  virtual void update(TdGame *game);
};

