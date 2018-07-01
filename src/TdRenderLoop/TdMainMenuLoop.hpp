#pragma once

/**
 * TrMainMenuLoop.hpp
 */

#include <string>
#include <vector>

#include "TdRenderLoop.hpp"

class TdGame;
class TdGUIEntity;
class TdGUISystem;

class TrMainMenuLoop : public TdRenderLoop {
public:
  std::string m_titleText = "Defense";
  SDL_Color textColor0 = {0, 255, 0, 255};
  int text_width;
  int text_height;

  sdl_texture_pt m_titleTexture;

  unique_ptr<TdGUISystem> m_GUISystem;
  TdGUIEntity *m_GUIMenu;

  explicit TrMainMenuLoop(TdGame *game);

  ~TrMainMenuLoop() override;

  TdRenderLoop *update(TdGame *game) override;
  void render(TdGame *game) override;
};