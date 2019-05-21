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

    addEnt(graphicsBackend.entVBOdata, cur_vertex_id, pos, w, b);
  }

  for (int i = 0; i < k_MAX_ENTS; i++) {
    int cur_vertex_id = i * triangles_per_ent * 3 * 3;

    if (!game->m_entitySystem->m_health.m_healthComponents[i].m_alive) {
      for (int j = 0; j < triangles_per_ent * 3 * 3; j++) {
        graphicsBackend.entcolorVBOdata[cur_vertex_id + j] = 0.0f;
      }
      continue;
    } else if (game->m_entitySystem->getEnt(i) == nullptr) {
      for (int j = 0; j < triangles_per_ent * 3 * 3; j++) {
        graphicsBackend.entcolorVBOdata[cur_vertex_id + j] = 0.0f;
      }
      continue;
    }

    for (int j = 0; j < triangles_per_ent * 3 * 3; j += 3) {
      float healthProp = game->m_entitySystem->m_health.m_healthComponents[i].m_curHealth /
          game->m_entitySystem->m_health.m_healthComponents[i].m_maxHealth;

      healthProp *= 0.5;
      healthProp += 0.5;

      auto ent = game->m_entitySystem->getEnt(i);
      if (ent) {
        if (ent->m_type == EntityType::ENEMY ||
            ent->m_type == EntityType::BOSS) {
          graphicsBackend.entcolorVBOdata[cur_vertex_id + j] = 1.0 * healthProp;
          graphicsBackend.entcolorVBOdata[cur_vertex_id + j+1] = 0.0;
          graphicsBackend.entcolorVBOdata[cur_vertex_id + j+2] = 0.0;
        } else {
          graphicsBackend.entcolorVBOdata[cur_vertex_id + j] = 1.0 * healthProp;
          graphicsBackend.entcolorVBOdata[cur_vertex_id + j+1] = 1.0 * healthProp;
          graphicsBackend.entcolorVBOdata[cur_vertex_id + j+2] = 1.0 * healthProp;
        }

      }
    }
  }
}