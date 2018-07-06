/**
 * TdECSGraphicsComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSGraphicsComponent.hpp"
#include <TdGame.hpp>

#include "../TdECSEntity.hpp"

void TdECSGraphicsComponent::update(TdGame *game, TdECSSystem *system) {
  SDL_Color c;
  SDL_GetRenderDrawColor(game->m_SDLRenderer, &c.r, &c.g, &c.b, &c.a);

  auto &ent = system->m_entities[m_entID];
  if (ent->has<TdECSHealthComponent>()) {
    auto healthComp = ent->get<TdECSHealthComponent>();
    SDL_SetRenderDrawColor(
        game->m_SDLRenderer, m_color.r, m_color.g, m_color.b,
        (0.2 + 0.8 * healthComp->m_curHealth / healthComp->m_maxHealth) *
            m_color.a);
  } else {
    SDL_SetRenderDrawColor(game->m_SDLRenderer, m_color.r, m_color.g, m_color.b,
                           m_color.a);
  }

  auto shape = system->m_entities[m_entID]->get<TdECSShapeComponent>();
  double xPos, yPos;
  std::tie(xPos, yPos) = getPosition(system->m_entities[m_entID].get());

  double xCenterPos, yCenterPos;
  std::tie(xCenterPos, yCenterPos) =
      getCenterPosition(system->m_entities[m_entID].get());

  for (int i = 0; i < shape->m_points.size() - 1; i++) {
    SDL_RenderDrawLine(game->m_SDLRenderer,
                       (int) std::round(xPos + shape->m_points[i].first),
                       (int) std::round(yPos + shape->m_points[i].second),
                       (int) std::round(xPos + shape->m_points[i + 1].first),
                       (int) std::round(yPos + shape->m_points[i + 1].second));
  }

  SDL_RenderDrawLine(game->m_SDLRenderer,
                     (int) std::round(xPos + shape->m_points.front().first),
                     (int) std::round(yPos + shape->m_points.front().second),
                     (int) std::round(xPos + shape->m_points.back().first),
                     (int) std::round(yPos + shape->m_points.back().second));

  if (system->m_entities[m_entID]->has<TdECSShooterComponent>()) {
    auto attackComp = system->m_entities[m_entID]->get<TdECSAttackComponent>();
    auto laserComp = system->m_entities[m_entID]->get<TdECSLaserShooterComponent>();
    if (laserComp->m_isShooting &&
        system->m_entities.count(attackComp->m_targetEntID)) {
      SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      double entXPos, entYPos;
      std::tie(entXPos, entYPos) = getCenterPosition(
          system->m_entities[attackComp->m_targetEntID].get());

      SDL_RenderDrawLine(game->m_SDLRenderer, (int) std::round(xCenterPos),
                         (int) std::round(yCenterPos), (int) std::round(entXPos),
                         std::round(entYPos));
    }
  }

  if (system->m_entities[m_entID]->has<TdECSFighterComponent>()) {
    auto attackComp = system->m_entities[m_entID]->get<TdECSAttackComponent>();
    auto laserComp = system->m_entities[m_entID]->get<TdECSLaserShooterComponent>();
    if (laserComp->m_isShooting &&
        system->m_entities.count(attackComp->m_targetEntID)) {
      SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0x00, 0x00, 0xFF);
      double entXPos, entYPos;
      std::tie(entXPos, entYPos) =
          getCenterPosition(system->m_entities[attackComp->m_targetEntID].get());

      SDL_RenderDrawLine(game->m_SDLRenderer, (int) std::round(xCenterPos),
                         (int) std::round(yCenterPos), (int) std::round(entXPos),
                         std::round(entYPos));
    }
  }

  SDL_SetRenderDrawColor(game->m_SDLRenderer, c.r, c.g, c.b, c.a);
}
