#pragma once

/**
 * TdGameLoop.hpp
 */

#include "Game.hpp"
#include "RenderLoop.hpp"

class ConstructionManager;
class LevelManager;
class GUIEntity;
class GUISystem;

class GameLoop : public RenderLoop {
 public:
  std::unique_ptr<ConstructionManager> m_constructionManager;
  std::unique_ptr<LevelManager> m_levelManager;

  explicit GameLoop(Game *game);

  ~GameLoop() override;

  RenderLoop *update(Game *game) override;
  void render(Game *game) override;
};