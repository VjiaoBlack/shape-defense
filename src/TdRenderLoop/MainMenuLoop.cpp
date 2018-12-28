/**
 * TrMainMenuLoop.cpp
 */

#include "MainMenuLoop.hpp"
#include "GameLoop.hpp"
#include "TransitionLoop.hpp"
#include <TdGUI/GUIEntity.hpp>

#include "TdGUI/TdGUIComponents/GUIGraphicsComponent.hpp"

MainMenuLoop::MainMenuLoop(Game *game) {
  sdl_surface_pt textSurface(TTF_RenderText_Solid(
      game->m_font.get(), m_titleText.c_str(), textColor0));

  m_titleTexture.reset(
      SDL_CreateTextureFromSurface(game->m_SDLRenderer, textSurface.get()));
  text_width = textSurface->w;
  text_height = textSurface->h;

  m_GUISystem = std::make_unique<GUISystem>();

  SDL_Rect r =
      (SDL_Rect){sz(K_DISPLAY_SIZE_X / 2 - 300 / 2),
                 sz(K_DISPLAY_SIZE_Y / 2 - text_height / 2),
                 sz(300), sz(K_DISPLAY_SIZE_Y / 3)};

  vector<string> labels = {"New Game", "Load Game", "Quit"};
  m_GUIMenu = GUIEntity::addVerticalMenu(game, m_GUISystem.get(), r,
                                           labels);
}

MainMenuLoop::~MainMenuLoop() = default;

RenderLoop *MainMenuLoop::update(Game *game) {
  if (m_GUIMenu->get<GUIContainerComponent>()
          ->m_buttons[0]
          ->get<GUIClickableComponent>()
          ->m_activated) {
    auto gameLoop = std::make_shared<GameLoop>(game);
    game->m_gameStateTransition = TransitionLoop::makePushLoop(
        game, game->m_gameStateStack.back(), gameLoop);

    game->m_gameStateStack.push_back(gameLoop);
  }

  if (m_GUIMenu->get<GUIContainerComponent>()
          ->m_buttons[2]
          ->get<GUIClickableComponent>()
          ->m_activated) {
    game->m_quit = true;
  }

  return nullptr;
}

void MainMenuLoop::render(Game *game) {
  SDL_Rect fillRect = {0, 0, sz(K_DISPLAY_SIZE_X), sz(K_DISPLAY_SIZE_Y)};

  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0x00, 0x00, 0x00, 0x40);

  SDL_RenderFillRect(game->m_SDLRenderer, &fillRect);

  // text
  SDL_Rect renderQuad = {
      sz(K_DISPLAY_SIZE_X / 2 - text_width / 2),
      sz(K_DISPLAY_SIZE_Y / 4 - text_height / 2),
      text_width * sz(1),
      text_height * sz(1)};

  SDL_RenderCopy(game->m_SDLRenderer, m_titleTexture.get(), nullptr, &renderQuad);

  m_GUISystem->update(game);
  game->m_entitySystem->m_graphics.update(game, game->m_entitySystem.get());
}
