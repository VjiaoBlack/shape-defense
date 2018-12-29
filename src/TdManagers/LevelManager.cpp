/** 
 * LevelManager.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include <Game.hpp>
#include <TdECS/Entity.hpp>
#include "LevelManager.hpp"
#include <Graphics.hpp>

LevelManager::LevelManager(Game *game) {
  LOG_INF("Created LevelManager");

  sdl_surface_pt textSurface(TTF_RenderText_Solid(
      game->m_font.get(), m_titleText.c_str(), textColor0));
  m_titleTexture.reset(
      SDL_CreateTextureFromSurface(game->m_SDLRenderer, textSurface.get()));
  text_width = textSurface->w;
  text_height = textSurface->h;

  m_rd = std::uniform_real_distribution<>(0.0, M_PI * 2);

  this->addRandomEnemy(game, 300);
  this->addRandomEnemy(game, 500);
  this->addRandomEnemy(game, 700);
  this->addRandomEnemy(game, 900);
}

void LevelManager::addRandomEnemy(Game *game, double dist) {
  double theta = m_rd(m_rg);
  double x = sin(theta) * dist + K_DISPLAY_SIZE_X / 2.0;
  double y = cos(theta) * dist + K_DISPLAY_SIZE_Y / 2.0;
  Entity::addEntity<EntityType::ENEMY>(game, game->m_entitySystem.get(), x, y);
}

void LevelManager::addRandomBoss(Game *game, double dist) {
  double theta = m_rd(m_rg);
  double x = sin(theta) * dist + K_DISPLAY_SIZE_X / 2.0;
  double y = cos(theta) * dist + K_DISPLAY_SIZE_Y / 2.0;
  Entity::addEntity<EntityType::BOSS>(game, game->m_entitySystem.get(), x, y);
}

void LevelManager::update(Game* game) {
  for (auto key : game->m_keysDown) {
    switch (key) {
      case SDLK_SPACE:
        this->addRandomEnemy(game, 1000);
        break;
    }
  }

  if (m_enemySpawnTimer >= m_nextEnemy) {
    if (m_curBossesSpawned > 0) {
      this->addRandomBoss(game, 1000);
      m_curBossesSpawned -= 1;
    } else {
      this->addRandomEnemy(game, 1000);
    }
    m_enemySpawnTimer = 0;
  }

  if (Entity::numDestroyed[(uint)EntityType::ENEMY] > m_curMarker) {
    if (m_enemySpawnTimer >= 2) {
      m_lastMarkerDist = m_lastMarkerDist * 1.5;
      m_curMarker += m_lastMarkerDist;
      m_enemySpawnTimer *= 4/5;
      LOG_INF("Difficulty increased... killed: %d, spawn: %d, marker: %d",
              Entity::numDestroyed[(uint)EntityType::ENEMY],
              m_enemySpawnTimer,
              m_curMarker);
      m_curLevel++;
      if (m_curLevel >= 2) {
        m_curBossesSpawned = m_curLevel - 1;
      }
    }
  }

  m_enemySpawnTimer++;
}

void LevelManager::render(Game* game) {
//  LOG_INF("Rendering LevelManager...");
//  LOG_INF("  Towers:  %d", Entity::numCreated[(uint)EntityType::TOWER] -
//                           Entity::numDestroyed[(uint)EntityType::TOWER]);
//  LOG_INF("  Enemies: %d", Entity::numCreated[(uint)EntityType::ENEMY] -
//                           Entity::numDestroyed[(uint)EntityType::ENEMY]);
//  LOG_INF("  Walls:   %d", Entity::numCreated[(uint)EntityType::WALL] -
//                           Entity::numDestroyed[(uint)EntityType::WALL]);
//  LOG_INF("  Enemies Destroyed: \t%d", Entity::numDestroyed[(uint)EntityType::ENEMY]);

  m_titleText = std::to_string(m_curLevel) + " " +
                std::to_string(Entity::numDestroyed[(uint)EntityType::ENEMY]) + " " +
                std::to_string(m_curMarker);
  sdl_surface_pt textSurface(TTF_RenderText_Solid(
      game->m_font.get(), m_titleText.c_str(), textColor0));
  m_titleTexture.reset(
      SDL_CreateTextureFromSurface(game->m_SDLRenderer, textSurface.get()));
  text_width = textSurface->w;
  text_height = textSurface->h;

  // text
  SDL_Rect renderQuad = {
      sz(K_DISPLAY_SIZE_X / 2 - text_width / 2),
      sz(K_DISPLAY_SIZE_Y / 4 - text_height / 2),
      text_width * sz(1),
      text_height * sz(1)};

  SDL_SetRenderDrawColor(game->m_SDLRenderer, 0x00, 0x00, 0x00, 0x40);
  SDL_RenderCopy(game->m_SDLRenderer, m_titleTexture.get(), nullptr, &renderQuad);
}
