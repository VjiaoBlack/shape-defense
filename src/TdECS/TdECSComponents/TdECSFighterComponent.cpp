/**
 * TdECSFighterComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSFighterComponent.hpp"
#include "../TdECSEntity.hpp"
#include "TdGame.hpp"

void TdECSFighterComponent::update(TdGame *game, TdECSSystem *system) {
  if (m_dead) {
    return;
  }
  if (system->m_entities.count(m_targetEntId) && system->m_entities[m_targetEntId] == nullptr) {
    m_targetEntId = -1;
  }
  if (!system->m_entities.count(m_entId) || system->m_entities[m_entId] == nullptr) {
    m_dead = true;
    return;
  }

  switch (m_target) {
    case 0:  // targets enemies
      break;
    case 1:
      if (m_targetEntId > -1) {
        // go towards it if its far
        double entX = -system->m_entities[m_entId]->get<TdECSPositionComponent>()->m_x;
        double entY = -system->m_entities[m_entId]->get<TdECSPositionComponent>()->m_y;
        if (system->m_entities[m_targetEntId]->has<TdECSPositionComponent>()) {
          entX += system->m_entities[m_targetEntId]->get<TdECSPositionComponent>()->m_x;
          entY += system->m_entities[m_targetEntId]->get<TdECSPositionComponent>()->m_y;
        } else if (system->m_entities[m_targetEntId]->has<TdECSTilePositionComponent>()) {
          entX += system->m_entities[m_targetEntId]->get<TdECSTilePositionComponent>()->m_x * 17 +
                  K_DISPLAY_SIZE_X / 2 - 8;
          entY += system->m_entities[m_targetEntId]->get<TdECSTilePositionComponent>()->m_y * 17 +
                  K_DISPLAY_SIZE_Y / 2 - 8;
        } else {
          printf("ERROR\n");
        }
        double distSq = entX * entX + entY * entY;

        if (distSq > 60.0 * 60.0) {
          // move towards it
          // TODO: make planning component
          system->m_entities[m_entId]->get<TdECSPhysicsComponent>()->m_vx = entX / sqrt(distSq);
          system->m_entities[m_entId]->get<TdECSPhysicsComponent>()->m_vy = entY / sqrt(distSq);
        } else {
          // stop
          // TODO: planning component
          system->m_entities[m_entId]->get<TdECSPhysicsComponent>()->m_vx = 0.0;
          system->m_entities[m_entId]->get<TdECSPhysicsComponent>()->m_vy = 0.0;
        }
      } else {
        if (system->m_entities.count(m_targetEntId) == 0) {
          m_targetEntId = -1;
        }
        double minDistSq = -1.0;


        for (auto& ent_pair : game->m_entitySystem->m_entities) {
          // if it's a shooter (assume all fighters are allies for now
          // TODO: assumption
          if (ent_pair.second->has<TdECSShooterComponent>()) {
            double entX;
            double entY;
            if (ent_pair.second->has<TdECSPositionComponent>()) {
              entX = ent_pair.second->get<TdECSPositionComponent>()->m_x;
              entY = ent_pair.second->get<TdECSPositionComponent>()->m_y;
            } else if (ent_pair.second->has<TdECSTilePositionComponent>()) {
              entX = ent_pair.second->get<TdECSTilePositionComponent>()->m_x * 17 +
                  K_DISPLAY_SIZE_X / 2 - 8;
              entY = ent_pair.second->get<TdECSTilePositionComponent>()->m_y * 17 +
                  K_DISPLAY_SIZE_Y / 2 - 8;
            }

            double myX = system->m_entities[m_entId]->get<TdECSPositionComponent>()->m_x;
            double myY = system->m_entities[m_entId]->get<TdECSPositionComponent>()->m_y;

            double distSq = (entX - myX) * (entX - myX) + (entY - myY) * (entY - myY);
            if (minDistSq < 0 || distSq < minDistSq) {
              minDistSq = distSq;
              m_targetEntId = ent_pair.first;
            }
            // and if it's close enough
            if (distSq < 10.0 * 10.0) {
              // attack it
              m_fighting = true;
            }
          }
        }
      }
      break;
  }
}