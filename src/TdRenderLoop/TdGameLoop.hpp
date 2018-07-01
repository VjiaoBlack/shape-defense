#pragma once

/**
 * TdGameLoop.hpp
 */

#include "../TdGame.hpp"
#include "TdRenderLoop.hpp"

using namespace std;

class TdGameLoop : public TdRenderLoop {
 public:
  std::default_random_engine m_rg;
  std::uniform_real_distribution<> m_rd;

  explicit TdGameLoop(TdGame *game);

  ~TdGameLoop() override;

  TdRenderLoop *update(TdGame *game) override;
  void render(TdGame *game) override;
};