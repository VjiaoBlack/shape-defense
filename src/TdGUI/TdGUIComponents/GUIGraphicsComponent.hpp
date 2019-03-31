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
#include <Utils.hpp>

class Game;

class GUIGraphicsComponent : public GUIComponent {
 public:
  MY_Rect m_rect;

  MY_Color m_buttonColor;
  MY_Color m_drawColor;

  Triangle m_rect1;
  Triangle m_rect2;
  GUIGraphicsComponent() = delete;

  GUIGraphicsComponent(MY_Rect rect) : m_rect(rect) {
    m_buttonColor = convertColorType(0xFF00FF00);

    m_drawColor = m_buttonColor;
    this->refresh();
  };

  ~GUIGraphicsComponent() {
    this->destroy();
  }

  void destroy() {
    m_rect1.destroy();
    m_rect2.destroy();
  }

  void refresh() {
    m_rect1 = Triangle(&graphicsBackend.guiVBOdata,
                       &graphicsBackend.guicolorVBOdata,
                       glm::vec2(m_rect.x, m_rect.y),
                       glm::vec2(m_rect.x + m_rect.w, m_rect.y),
                       glm::vec2(m_rect.x + m_rect.w, m_rect.y + m_rect.h),
                       glm::vec3(1.0, 0.0, 1.0));

    m_rect2 = Triangle(&graphicsBackend.guiVBOdata,
                       &graphicsBackend.guicolorVBOdata,
                       glm::vec2(m_rect.x, m_rect.y),
                       glm::vec2(m_rect.x, m_rect.y + m_rect.h),
                       glm::vec2(m_rect.x + m_rect.w, m_rect.y + m_rect.h),
                       glm::vec3(1.0, 0.0, 1.0));
  }

  virtual void update(Game *game);
};

