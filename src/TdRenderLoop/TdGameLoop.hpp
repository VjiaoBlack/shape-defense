#pragma once

/**
 * TdGameLoop.hpp
 */

#include "../TdGame.hpp"
#include "TdRenderLoop.hpp"

class TdConstructionManager;

class TdGameLoop : public TdRenderLoop {
 private:
  void addRandomEnemy(TdGame* game, double dist);

 public:
  std::default_random_engine m_rg;
  std::uniform_real_distribution<> m_rd;

  bool m_isBuilding = false;

  std::unique_ptr<TdConstructionManager> m_constructionManager;

  explicit TdGameLoop(TdGame *game);

  ~TdGameLoop() override;

  TdRenderLoop *update(TdGame *game) override;
  void render(TdGame *game) override;
};