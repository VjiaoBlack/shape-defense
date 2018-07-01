#pragma once

/**
 * TrTransitionLoop.hpp
 */

#include "TdRenderLoop.hpp"

#include <memory>
#include <utility>
class TrTransitionLoop : public TdRenderLoop {
 private:
  shared_ptr<TdRenderLoop> m_target;
  shared_ptr<TdRenderLoop> m_source;
  // TODO: initialize here or in ctor?
  int m_maxTicks = 80;
  int m_curTick = 0;
  int m_maxWaitTick = 20;
  int m_waitTick = 0;
  bool m_deleteSource;
  TrTransitionLoop(TdGame *game,
                   shared_ptr<TdRenderLoop> source,
                   shared_ptr<TdRenderLoop> target,
                   bool deleteSource)
      : m_target(std::move(target)), m_source(std::move(source)), m_deleteSource(deleteSource) {};

 public:
  ~TrTransitionLoop() override {
//    if (m_deleteSource) delete m_source;
  };

  static unique_ptr<TrTransitionLoop> makePushLoop(TdGame *game, shared_ptr<TdRenderLoop>
  source,
                                                   shared_ptr<TdRenderLoop> target) {
    return unique_ptr<TrTransitionLoop>(new TrTransitionLoop(game, std::move(source),
                                                             std::move(target), false));
  }

  static unique_ptr<TrTransitionLoop> makePopLoop(TdGame *game, shared_ptr<TdRenderLoop>
  source,
                                                  shared_ptr<TdRenderLoop> target) {
    return unique_ptr<TrTransitionLoop>(new TrTransitionLoop(game, std::move(source),
                                                             std::move(target), true));
  }

  TdRenderLoop *update(TdGame *game) override;
  void render(TdGame *game) override;
  inline void setTarget(shared_ptr<TdRenderLoop> target) { m_target = std::move(target); }
  inline void setSource(shared_ptr<TdRenderLoop> source) { m_source = std::move(source); }

  // TODO: make a stack of TdRenderLoops inside of TdGame
};
