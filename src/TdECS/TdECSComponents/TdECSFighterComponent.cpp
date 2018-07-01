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

void TdECSFighterComponent::update(TdGame* game) {
  switch (m_target) {
    case 0:  // targets enemies
      break;
    case 1:
      if (m_targetEnt) {
        // go towards it if its far
        double entX = -m_ent->get<TdECSPositionComponent>()->m_x;
        double entY = -m_ent->get<TdECSPositionComponent>()->m_y;
        if (m_targetEnt->has<TdECSPositionComponent>()) {
          entX += m_targetEnt->get<TdECSPositionComponent>()->m_x;
          entY += m_targetEnt->get<TdECSPositionComponent>()->m_y;
        } else if (m_targetEnt->has<TdECSTilePositionComponent>()) {
          entX += m_targetEnt->get<TdECSTilePositionComponent>()->m_x * 17 +
                  K_DISPLAY_SIZE_X / 2 - 8;
          entY += m_targetEnt->get<TdECSTilePositionComponent>()->m_y * 17 +
                  K_DISPLAY_SIZE_Y / 2 - 8;
        } else {
          printf("ERROR\n");
        }
        double distSq = entX * entX + entY * entY;

        if (distSq > 60.0 * 60.0) {
          // move towards it
          // TODO: make planning component
          m_ent->get<TdECSPhysicsComponent>()->m_vx = 3.0 * entX / sqrt(distSq);
          m_ent->get<TdECSPhysicsComponent>()->m_vy = 3.0 * entY / sqrt(distSq);
        } else {
          // stop
          // TODO: planning component
          m_ent->get<TdECSPhysicsComponent>()->m_vx = 0.0;
          m_ent->get<TdECSPhysicsComponent>()->m_vy = 0.0;
        }
      } else {
        double minDistSq = -1.0;
        for (auto& ent : game->m_entitySystem->m_entities) {
          // if it's a shooter (assume all fighters are allies for now
          // TODO: assumption
          if (ent->has<TdECSShooterComponent>()) {
            printf("found potential target\n");
            double entX;
            double entY;
            if (ent->has<TdECSPositionComponent>()) {
              entX = ent->get<TdECSPositionComponent>()->m_x;
              entY = ent->get<TdECSPositionComponent>()->m_y;
            } else if (ent->has<TdECSTilePositionComponent>()) {
              entX = ent->get<TdECSTilePositionComponent>()->m_x * 17;
              entY = ent->get<TdECSTilePositionComponent>()->m_y * 17;
            }
            double distSq = entX * entX + entY * entY;
            if (minDistSq < 0 || distSq < minDistSq) {
              minDistSq = distSq;
              m_targetEnt = ent.get();
              printf("Target Found!: %f, %f\n",
                     m_ent->get<TdECSPositionComponent>()->m_x,
                     m_ent->get<TdECSPositionComponent>()->m_y);
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