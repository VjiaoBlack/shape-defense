#pragma once

/**
 * TdGameLoop.hpp
 */

#include "Game.hpp"
#include "RenderLoop.hpp"

class ConstructionManager;
class LevelManager;
class HeatMapManager;
class GUIEntity;
class GUISystem;

class GameLoop : public RenderLoop {
 public:
  std::unique_ptr<ConstructionManager> m_constructionManager;
  std::unique_ptr<LevelManager>        m_levelManager;
  std::unique_ptr<HeatMapManager>      m_heatMapManager;

  Triangle m_moneyBar1;
  Triangle m_moneyBar2;

  Triangle m_energyBar1;
  Triangle m_energyBar2;

  explicit GameLoop(Game *game);

  ~GameLoop() override;

  RenderLoop *update(Game *game) override;
  void        render(Game *game) override;
};