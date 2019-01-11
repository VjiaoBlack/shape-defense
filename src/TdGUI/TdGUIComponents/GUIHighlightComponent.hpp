#pragma once
/**
 * TdGUIHighlightComponent.hpp
 *
 * Victor Jiao
 *
 * Enables components to have highlights
 */

#include "GUIComponent.hpp"
#include "GUIMouseComponent.hpp"
#include <memory>

class GUIHighlightComponent : public GUIComponent {
 public:
  MY_Color m_highlightColor;

  GUIHighlightComponent() {
    m_highlightColor.r = 0xFF;
    m_highlightColor.g = 0xFF;
    m_highlightColor.b = 0x80;
    m_highlightColor.a = 0x80;
  };

  virtual void update(Game *game);
};

