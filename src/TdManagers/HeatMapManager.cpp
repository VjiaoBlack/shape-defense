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
  std::fill(std::begin(m_tiles), std::end(m_tiles), 0);
  std::fill(std::begin(m_tmp  ), std::end(m_tmp  ), 0);
}

void HeatMapManager::update(Game* game) {
  // go thru all the entities???
  for (auto ent : game->m_entitySystem->m_enemies) {
    if (ent.m_alive) {
      auto pos = ent.getPosition();

      // hmmmm
      int x = (int) pos.x / 16 - 50;
      int y = (int) pos.y / 16 - 28;

      x += World::dim.x / 2;
      y += World::dim.y / 2;

      if (x >= 0 && y >= 0 && x < World::dim.x && y < World::dim.y) {
        // tweak this to be "in between" a set and add
        m_tiles[x + y * World::dim.x] = 100.0;
      }
    }
  }

  for (int x = 0; x < World::dim.x; x++) {
    for (int y = 0; y < World::dim.y; y++) {
      int numTiles = 0;
      double tileTotal = 0;

      if (x - 1 >= 0 && x - 1 < World::size &&
          y     >= 0 && y     < World::size) {
        tileTotal += m_tiles[x - 1 + y * World::dim.x];
        numTiles++;
      }

      if (x + 1 >= 0 && x + 1 < World::size &&
          y     >= 0 && y     < World::size) {
        tileTotal += m_tiles[x + 1 + y * World::dim.x];
        numTiles++;
      }

      if (x     >= 0 && x     < World::size &&
          y - 1 >= 0 && y - 1 < World::size) {
        tileTotal += m_tiles[x + (y - 1) * World::dim.x];
        numTiles++;
      }

      if (x     >= 0 && x     < World::size &&
          y + 1 >= 0 && y + 1 < World::size) {
        tileTotal += m_tiles[x + (y + 1) * World::dim.x];
        numTiles++;
      }

      if (numTiles) {
        m_tmp[x + y * World::dim.x] *= 0.2;
        m_tmp[x + y * World::dim.x] += 0.8 * tileTotal / numTiles;
      }

      if (m_tmp[x + y * World::dim.x] > 0) {
        m_tmp[x + y * World::dim.x] *= 0.99;
      }
    }
  }

  double sum = 0;
  for (int x = 0; x < World::dim.x; x++) {
    for (int y = 0; y < World::dim.y; y++) {
      m_tiles[x + y * World::dim.x] = m_tmp[x + y * World::dim.x];
    }
  }

  // ??? update to graphics ???
  glBindTexture(GL_TEXTURE_2D, graphicsBackend.heatmapTex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, World::dim.x, World::dim.y, 0, GL_RED, GL_FLOAT, m_tiles.data());
}