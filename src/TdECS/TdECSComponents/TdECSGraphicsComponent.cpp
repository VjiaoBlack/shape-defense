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

void TdECSGraphicsComponent::update(TdGame *game) {
  SDL_Color c;
  SDL_GetRenderDrawColor(game->m_SDLRenderer, &c.r, &c.g, &c.b, &c.a);

  SDL_SetRenderDrawColor(game->m_SDLRenderer, m_color.r, m_color.g, m_color.b,
                         m_color.a);

  auto shape = m_ent->get<TdECSShapeComponent>();
  double xPos;
  double yPos;

  if (m_ent->has<TdECSTilePositionComponent>()) {
    xPos = m_ent->get<TdECSTilePositionComponent>()->m_x * 17 +
           K_DISPLAY_SIZE_X / 2 - 8;
    yPos = m_ent->get<TdECSTilePositionComponent>()->m_y * 17 +
           K_DISPLAY_SIZE_Y / 2 - 8;
  } else {
    xPos = m_ent->get<TdECSPositionComponent>()->m_x;
    yPos = m_ent->get<TdECSPositionComponent>()->m_y;
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

  if (m_ent->has<TdECSShooterComponent>()) {
    auto shooterComp = m_ent->get<TdECSShooterComponent>();
    if (shooterComp->m_isShooting) {
      SDL_RenderDrawLine(
          game->m_SDLRenderer, (int)std::round(xPos), (int)std::round(yPos),
          (int)std::round(
              shooterComp->m_targetEnt->get<TdECSPositionComponent>()->m_x),
          (int)std::round(
              shooterComp->m_targetEnt->get<TdECSPositionComponent>()->m_y));
    }
  }

  SDL_SetRenderDrawColor(game->m_SDLRenderer, c.r, c.g, c.b, c.a);
}
