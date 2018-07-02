/**
 * TdECSGraphicsComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSGraphicsComponent.hpp"
#include <TdGame.hpp>
#include "TdECSShapeComponent.hpp"

#include "../TdECSEntity.hpp"

void TdECSGraphicsComponent::update(TdGame *game, TdECSSystem *system) {
  SDL_Color c;
  SDL_GetRenderDrawColor(game->m_SDLRenderer, &c.r, &c.g, &c.b, &c.a);

  SDL_SetRenderDrawColor(game->m_SDLRenderer, m_color.r, m_color.g, m_color.b,
                         m_color.a);

  auto shape = system->m_entities[m_entId]->get<TdECSShapeComponent>();
  double xPos;
  double yPos;

  if (system->m_entities[m_entId]->has<TdECSTilePositionComponent>()) {
    xPos = system->m_entities[m_entId]->get<TdECSTilePositionComponent>()->m_x * 17 +
           K_DISPLAY_SIZE_X / 2 - 8;
    yPos = system->m_entities[m_entId]->get<TdECSTilePositionComponent>()->m_y * 17 +
           K_DISPLAY_SIZE_Y / 2 - 8;
  } else {
    xPos = system->m_entities[m_entId]->get<TdECSPositionComponent>()->m_x;
    yPos = system->m_entities[m_entId]->get<TdECSPositionComponent>()->m_y;
  }

  for (int i = 0; i < shape->m_points.size() - 1; i++) {
    SDL_RenderDrawLine(game->m_SDLRenderer,
                       (int)std::round(xPos + shape->m_points[i].first),
                       (int)std::round(yPos + shape->m_points[i].second),
                       (int)std::round(xPos + shape->m_points[i + 1].first),
                       (int)std::round(yPos + shape->m_points[i + 1].second));
  }

  SDL_RenderDrawLine(game->m_SDLRenderer,
                     (int)std::round(xPos + shape->m_points.front().first),
                     (int)std::round(yPos + shape->m_points.front().second),
                     (int)std::round(xPos + shape->m_points.back().first),
                     (int)std::round(yPos + shape->m_points.back().second));

  if (system->m_entities[m_entId]->has<TdECSShooterComponent>()) {
    auto shooterComp = system->m_entities[m_entId]->get<TdECSShooterComponent>();
    if (shooterComp->m_isShooting && system->m_entities.count(shooterComp->m_targetEntId)) {
      // TODO: problem with deleted targets while shooting...
      // TODO: probably from when 2 shooters target
      SDL_RenderDrawLine(
          game->m_SDLRenderer, (int)std::round(xPos), (int)std::round(yPos),
          (int)std::round(
              system->m_entities[shooterComp->m_targetEntId]->get<TdECSPositionComponent>()->m_x),
          (int)std::round(
              system->m_entities[shooterComp->m_targetEntId]->get<TdECSPositionComponent>()->m_y));
    }
  }

  SDL_SetRenderDrawColor(game->m_SDLRenderer, c.r, c.g, c.b, c.a);
}
