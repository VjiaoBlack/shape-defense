#pragma once

/**
 * TdGameLoop.hpp
 */

#include "../TdGame.hpp"
#include "TdRenderLoop.hpp"

using namespace std;

class TdGameLoop : public TdRenderLoop {
 public:
  explicit TdGameLoop(TdGame *game);

  ~TdGameLoop() override;

  TdRenderLoop *update(TdGame *game) override;
  void render(TdGame *game) override;
};