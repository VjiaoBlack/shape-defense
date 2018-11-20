#pragma once

/**
 * TrTransitionLoop.hpp
 */

#include "RenderLoop.hpp"

#include <memory>
#include <utility>
class TransitionLoop : public RenderLoop {
 private:
  shared_ptr<RenderLoop> m_target;
  shared_ptr<RenderLoop> m_source;
  // TODO: initialize here or in ctor?
  int m_maxTicks = 40;
  int m_curTick = 0;
  int m_maxWaitTick = 20;
  int m_waitTick = 0;
  bool m_deleteSource;
  TransitionLoop(Game *game,
                   shared_ptr<RenderLoop> source,
                   shared_ptr<RenderLoop> target,
                   bool deleteSource)
      : m_target(std::move(target)), m_source(std::move(source)), m_deleteSource(deleteSource) {};

 public:
  ~TransitionLoop() override {
//    if (m_deleteSource) delete m_source;
  };

  static unique_ptr<TransitionLoop> makePushLoop(Game *game, shared_ptr<RenderLoop>
  source,
                                                   shared_ptr<RenderLoop> target) {
    return unique_ptr<TransitionLoop>(new TransitionLoop(game, std::move(source),
                                                             std::move(target), false));
  }

  static unique_ptr<TransitionLoop> makePopLoop(Game *game, shared_ptr<RenderLoop>
  source,
                                                  shared_ptr<RenderLoop> target) {
    return unique_ptr<TransitionLoop>(new TransitionLoop(game, std::move(source),
                                                             std::move(target), true));
  }

  RenderLoop *update(Game *game) override;
  void render(Game *game) override;
  inline void setTarget(shared_ptr<RenderLoop> target) { m_target = std::move(target); }
  inline void setSource(shared_ptr<RenderLoop> source) { m_source = std::move(source); }

  // TODO: make a stack of TdRenderLoops inside of Game
};
