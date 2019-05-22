/**
 * HeatMapManager.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "HeatMapManager.hpp"
#include "ECS/Entity.hpp"
#include "Game.hpp"

HeatMapManager::HeatMapManager(Game* game) {
  for (int x = 0; x < 56; x++) {
    for (int y = 0; y < 56; y++) {
      m_vis[x + y * 56] = Triangle(
          &graphicsBackend.guiVBOdata,
          &graphicsBackend.guicolorVBOdata,
          glm::vec2(K_DISPLAY_SIZE_X / 2 + 50 + (x - 24) * 16,      K_DISPLAY_SIZE_Y / 2 + 28 + (y - 24) * 16),
          glm::vec2(K_DISPLAY_SIZE_X / 2 + 50 + (x - 24) * 16 + 10, K_DISPLAY_SIZE_Y / 2 + 28 + (y - 24) * 16),
          glm::vec2(K_DISPLAY_SIZE_X / 2 + 50 + (x - 24) * 16 + 10, K_DISPLAY_SIZE_Y / 2 + 28 + (y - 24) * 16 + 10),
          glm::vec3(0.0, 0.0, 0.0));
    }
  }
}

void HeatMapManager::update(Game* game) {
  // go thru all the entities???
  for (auto ent : game->m_entitySystem->m_enemies) {
    if (ent.m_alive) {
      auto pos = ent.getPosition();

      int x = (int) pos.x / 16 - 50 - 3;
      int y = (int) pos.y / 16 - 28 - 2;

      x += 24;
      y += 24;

      if (x >= 0 && y >= 0 && x < 56 && y < 56) {
        m_tiles[x + y * 56] = 100.0;
      }
    }
  }

  for (int x = 0; x < 56; x++) {
    for (int y = 0; y < 56; y++) {
      int numTiles = 0;
      double tileTotal = 0;

      if (x - 1 >= 0 && x - 1 < 56 &&
          y     >= 0 && y     < 56) {
        tileTotal += m_tiles[x - 1 + y * 56];
        numTiles++;
      }

      if (x + 1 >= 0 && x + 1 < 56 &&
          y     >= 0 && y     < 56) {
        tileTotal += m_tiles[x + 1 + y * 56];
        numTiles++;
      }

      if (x     >= 0 && x     < 56 &&
          y - 1 >= 0 && y - 1 < 56) {
        tileTotal += m_tiles[x + (y - 1) * 56];
        numTiles++;
      }

      if (x     >= 0 && x     < 56 &&
          y + 1 >= 0 && y + 1 < 56) {
        tileTotal += m_tiles[x + (y + 1) * 56];
        numTiles++;
      }

      if (numTiles) {
        m_tmp[x + y * 56] *= 0.2;
        m_tmp[x + y * 56] += 0.8 * tileTotal / numTiles;
      }

      if (m_tmp[x + y * 56] > 0) {
        m_tmp[x + y * 56] *= 0.96;
      }
    }
  }

  for (int x = 0; x < 56; x++) {
    for (int y = 0; y < 56; y++) {
      m_tiles[x + y * 56] = m_tmp[x + y * 56];

      m_vis[x + y * 56].update(glm::vec3(1.0, 1.0, 1.0) * (float) m_tiles[x + y * 56] / 100.0f);
    }
  }
}