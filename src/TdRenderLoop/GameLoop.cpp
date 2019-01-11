/**
 * TdGameLoop.cpp
 */

#include "GameLoop.hpp"
#include <TdManagers/ConstructionManager.hpp>
#include <TdManagers/LevelManager.hpp>
#include "TdECS/Entity.hpp"
#include "MainMenuLoop.hpp"
#include "TransitionLoop.hpp"

class MainMenuLoop;

void addTriangle(std::vector<GLfloat>& buf, int pos, glm::vec2 a, glm::vec2 b, glm::vec2 c) {
  graphicsBackend.entVBOdata[pos + 0] = a.x;
  graphicsBackend.entVBOdata[pos + 1] = a.y;
  graphicsBackend.entVBOdata[pos + 2] = 0.0f;

  graphicsBackend.entVBOdata[pos + 3] = b.x;
  graphicsBackend.entVBOdata[pos + 4] = b.y;
  graphicsBackend.entVBOdata[pos + 5] = 0.0f;

  graphicsBackend.entVBOdata[pos + 6] = c.x;
  graphicsBackend.entVBOdata[pos + 7] = c.y;
  graphicsBackend.entVBOdata[pos + 8] = 0.0f;
}


GameLoop::GameLoop(Game *game) {
  m_constructionManager = std::make_unique<ConstructionManager>(game);
  m_levelManager = std::make_unique<LevelManager>(game);
}

GameLoop::~GameLoop() = default;

RenderLoop *GameLoop::update(Game *game) {
  auto penu = game->m_gameStateStack.end();

  for (auto key : game->m_keysDown) {
    switch (key) {
      case GLFW_KEY_V:
        penu--;
        penu--;

        game->m_gameStateTransition = TransitionLoop::makePopLoop(
            game, game->m_gameStateStack.back(), *penu);
        game->m_gameStateStack.pop_back();

        break;
    }
  }

  m_constructionManager->update(game);
  m_levelManager->update(game);

  game->m_entitySystem->update(game, false);

  return this;
}

void GameLoop::render(Game *game) {
  game->m_entitySystem->m_graphics.update(game, game->m_entitySystem.get());

  // Clear the screen
  glClear( GL_COLOR_BUFFER_BIT );

  // Use our shader
  glUseProgram(graphicsBackend.gridShader);

  // draw background grid
  glBindVertexArray(graphicsBackend.gridVAO);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, graphicsBackend.gridvertexVBO);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glDrawArrays(GL_LINES, 0, graphicsBackend.gridVBOdata.size());

  // draw ents
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glUseProgram(graphicsBackend.entShader);
  glBindVertexArray(graphicsBackend.entVAO);

  // ent shapes
  glEnableVertexAttribArray(0);
  GraphicsBackend::updateVBO(graphicsBackend.entvertexVBO,
                             graphicsBackend.entVBOdata.data(),
                             sizeof(GLfloat) * graphicsBackend.entVBOdata.size());
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  // ent healths
  glEnableVertexAttribArray(1);
  GraphicsBackend::updateVBO(graphicsBackend.enthealthVBO,
                             graphicsBackend.enthealthVBOdata.data(),
                             sizeof(GLfloat) * graphicsBackend.enthealthVBOdata.size());
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, graphicsBackend.entVBOdata.size());

  glDisableVertexAttribArray(1);

  // draw effects
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glUseProgram(graphicsBackend.gridShader);
  glBindVertexArray(graphicsBackend.effectVAO);
  glEnableVertexAttribArray(0);
  GraphicsBackend::updateVBO(graphicsBackend.effectVBO,
                             graphicsBackend.effectVBOdata.data(),
                             sizeof(GLfloat) * graphicsBackend.effectVBOdata.size());
  glBindBuffer(GL_ARRAY_BUFFER, graphicsBackend.effectVBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, graphicsBackend.effectVBOdata.size());

  // draw GUI
  glUseProgram(graphicsBackend.gridShader);
  glBindVertexArray(graphicsBackend.guiVAO);
  glEnableVertexAttribArray(0);
  GraphicsBackend::updateVBO(graphicsBackend.guiVBO,
                             graphicsBackend.guiVBOdata.data(),
                             sizeof(GLfloat) * graphicsBackend.guiVBOdata.size());
  glBindBuffer(GL_ARRAY_BUFFER, graphicsBackend.guiVBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, graphicsBackend.guiVBOdata.size());

  glDisableVertexAttribArray(0);

  // Swap buffers
  glfwSwapBuffers(graphicsBackend.window);
  glfwPollEvents();

  // draw money
//  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0x80);
//  SDL_RenderDrawLine(game->m_SDLRenderer, 50, 50, 50 + (int) game->m_maxMoney * 2.0, 50);
//
//  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0x80, 0x80, 0xFF, 0x80);
//  SDL_RenderDrawLine(game->m_SDLRenderer, 50, 75, 50 + (int) game->m_maxEnergy * 2.0, 75);
//
//  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//  SDL_RenderDrawLine(game->m_SDLRenderer, 50, 50, 50 + (int) game->m_curMoney * 2.0, 50);
//
//  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0x80, 0x80, 0xFF, 0xFF);
//  SDL_RenderDrawLine(game->m_SDLRenderer, 50, 75, 50 + (int) game->m_curEnergy * 2.0, 75);

  m_constructionManager->render(game);
  m_levelManager->render(game);
}
