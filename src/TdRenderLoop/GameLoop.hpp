#pragma once

/**
 * TdGameLoop.hpp
 */

#include "Game.hpp"
#include "RenderLoop.hpp"

class ConstructionManager;

class GameLoop : public RenderLoop {
 private:
  void addRandomEnemy(Game* game, double dist);

 public:
  std::default_random_engine m_rg;
  std::uniform_real_distribution<> m_rd;

  int m_enemySpawnTimer = 0;

  std::unique_ptr<ConstructionManager> m_constructionManager;

  explicit GameLoop(Game *game);

  ~GameLoop() override;

  RenderLoop *update(Game *game) override;
  void render(Game *game) override;
};