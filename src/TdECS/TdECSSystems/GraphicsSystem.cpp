/** 
 * TdECSGraphicsSystem.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "../../Game.hpp"
#include "GraphicsSystem.hpp"
#include "../Entity.hpp"

void GraphicsSystem::update(Game *game, System* system) {
  updateComponents(game, system, m_graphicsComponents);

  // update openGL stuff
  for (int i = 0; i < k_MAX_ENTS; i++) {
    int cur_vertex_id = i * triangles_per_ent * 9;

    if (!game->m_entitySystem->m_health.m_healthComponents[i].m_alive) {
      for (int j = 0; j < triangles_per_ent * 9; j++) {
        graphicsBackend.entVBOdata[cur_vertex_id + j] = 0.0f;
      }
      continue;
    } else if (game->m_entitySystem->getEnt(i) == nullptr) {
      for (int j = 0; j < triangles_per_ent * 9; j++) {
        graphicsBackend.entVBOdata[cur_vertex_id + j] = 0.0f;
      }
      continue;
    }

    glm::dvec2 pos = game->m_entitySystem->getEnt(i)->getPosition();
    int w = EntityShapes[(uint)game->m_entitySystem->getEnt(i)->m_type].w;
    int h = EntityShapes[(uint)game->m_entitySystem->getEnt(i)->m_type].h;

    int b = 2;
    // left
    addTriangle(graphicsBackend.entVBOdata, cur_vertex_id + 9 * 0,
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(b, 0),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(0, h));

    addTriangle(graphicsBackend.entVBOdata, cur_vertex_id + 9 * 1,
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(b, 0),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(b, h),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(0, h));

    // right
    addTriangle(graphicsBackend.entVBOdata, cur_vertex_id + 9 * 2,
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w, 0),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w-b, 0),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w-b, h));

    addTriangle(graphicsBackend.entVBOdata, cur_vertex_id + 9 * 3,
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w, 0),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w, h),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w-b, h));

    // bottom
    addTriangle(graphicsBackend.entVBOdata, cur_vertex_id + 9 * 4,
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(b, 0),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w-b, 0),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w-b, b));

    addTriangle(graphicsBackend.entVBOdata, cur_vertex_id + 9 * 5,
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(b, 0),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(b, b),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w-b, b));

    // top
    addTriangle(graphicsBackend.entVBOdata, cur_vertex_id + 9 * 6,
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(b, h),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w-b, h),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w-b,
                                                                                          h-b));

    addTriangle(graphicsBackend.entVBOdata, cur_vertex_id + 9 * 7,
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(b, h),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(b, h-b),
                pos - glm::dvec2(K_DISPLAY_SIZE_X / 2, K_DISPLAY_SIZE_Y / 2) + glm::dvec2(w-b,
                                                                                          h-b));
  }

  for (int i = 0; i < k_MAX_ENTS; i++) {
    int cur_vertex_id = i * triangles_per_ent * 3;

    if (!game->m_entitySystem->m_health.m_healthComponents[i].m_alive) {
      for (int j = 0; j < triangles_per_ent * 3; j++) {
        graphicsBackend.enthealthVBOdata[cur_vertex_id + j] = 0.0f;
      }
      continue;
    } else if (game->m_entitySystem->getEnt(i) == nullptr) {
      for (int j = 0; j < triangles_per_ent * 3; j++) {
        graphicsBackend.enthealthVBOdata[cur_vertex_id + j] = 0.0f;
      }
      continue;
    }

    for (int j = 0; j < triangles_per_ent * 3; j++) {
      graphicsBackend.enthealthVBOdata[cur_vertex_id + j] =
          game->m_entitySystem->m_health.m_healthComponents[i].m_curHealth /
              game->m_entitySystem->m_health.m_healthComponents[i].m_maxHealth;
    }
  }
}