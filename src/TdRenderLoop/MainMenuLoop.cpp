/**
 * TrMainMenuLoop.cpp
 */

#include "MainMenuLoop.hpp"
#include "GameLoop.hpp"

#include <TdGUI/GUIEntity.hpp>
#include <TdGUI/TdGUIComponents/GUIGraphicsComponent.hpp>

MainMenuLoop::MainMenuLoop(Game *game) {
  m_GUISystem = std::make_unique<GUISystem>();

  vector<string> labels = {"New Game", "Load Game", "Quit"};
  MY_Rect        r      = (MY_Rect) {sz(K_DISPLAY_SIZE_X / 2 - 300 / 2),
                                     sz(-text_height / 2),
                                     sz(300),
                                     sz(K_DISPLAY_SIZE_Y / 3)};

  m_GUIMenu = GUIEntity::addVerticalMenu(game,
                                         m_GUISystem.get(),
                                         r,
                                         labels);

  // both these callbacks are '=' because the only used param is game, a passed in pointer
  m_GUIMenu->get<GUIContainerComponent>()
      ->m_buttons[0]
      ->get<GUIClickableComponent>()
      ->setCallback([=]() {
        for (auto &g : m_GUISystem->m_graphics.m_graphicsComponents) {
          g->destroy();
        }
        auto gameLoop = std::make_shared<GameLoop>(game);
        game->m_gameStateStack.push_back(gameLoop);
      });

  m_GUIMenu->get<GUIContainerComponent>()
      ->m_buttons[2]
      ->get<GUIClickableComponent>()
      ->setCallback([=]() { game->m_quit = true; });
}

MainMenuLoop::~MainMenuLoop() = default;

RenderLoop *MainMenuLoop::update(Game *game) {
  return nullptr;
}

void MainMenuLoop::render(Game *game) {
  MY_Rect fillRect = {0, 0, sz(K_DISPLAY_SIZE_X), sz(K_DISPLAY_SIZE_Y)};

  // SDL_RenderFillRect(game->m_SDLRenderer, &fillRect);

  // text
  MY_Rect renderQuad = {sz(K_DISPLAY_SIZE_X / 2 - text_width / 2),
                        sz(K_DISPLAY_SIZE_Y / 4 - text_height / 2),
                        text_width * sz(1),
                        text_height * sz(1)};

  // SDL_RenderCopy(game->m_SDLRenderer, m_titleTexture.get(), nullptr, &renderQuad);

  m_GUISystem->update(game);
  game->m_entitySystem->m_graphics.update(game, game->m_entitySystem.get());


}
