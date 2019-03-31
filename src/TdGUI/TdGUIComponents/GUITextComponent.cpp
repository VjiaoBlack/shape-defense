/**
 * TdGUITextComponent.cpp
 *
 * Victor Jiao
 *
 * Makes entities clickable
 */

#include <TdGUI/TdGUIComponents/GUITextComponent.hpp>
#include <Game.hpp>

GUITextComponent::GUITextComponent(Game        *game,
                                   std::string  label,
                                   MY_Rect      r)
    : m_text(label)
    , m_destRect(r) {
  m_textColor.a = 0xFF;
  m_textColor.r = 0x00;
  m_textColor.g = 0xFF;
  m_textColor.b = 0x00;

  m_destRect.x = r.x + (r.w - m_destRect.w) / 2;
  m_destRect.y = r.y + (r.h - m_destRect.h) / 2;
}

void GUITextComponent::update(Game *game) {
  float   sx     = 2.0 / K_DISPLAY_SIZE_X;
  float   sy     = 2.0 / K_DISPLAY_SIZE_Y;
  GLfloat red[4] = {1, 0, 0, 1};

  FT_Set_Pixel_Sizes(graphicsBackend.face, 0, 48);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glUniform4fv(graphicsBackend.uniform_color, 1, red);
  glUseProgram(graphicsBackend.textShader);

  graphicsBackend.render_text(m_text.c_str(), -1 + m_destRect.x * sx, m_destRect.y * sy - 1, sx, sy);
  glDisable(GL_BLEND);
}
