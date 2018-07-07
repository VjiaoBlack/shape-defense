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

  auto ent = system->m_entities[m_entID].get();
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

  auto shape = ent->get<TdECSShapeComponent>();
  double xPos, yPos;
  std::tie(xPos, yPos) = getPosition(ent);

  double xCenterPos, yCenterPos;
  std::tie(xCenterPos, yCenterPos) =
      getCenterPosition(ent);

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

  if (ent->has<TdECSLaserShooterComponent>()) {
    auto attackComp = ent->get<TdECSAttackComponent>();
    auto laserComp =
        ent->get<TdECSLaserShooterComponent>();
    if (laserComp->m_isShooting &&
        system->m_entities.count(attackComp->m_targetEntID)) {
      if (ent->has<TdECSShooterComponent>()) {
        SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      } else if (ent->has<TdECSFighterComponent>()) {
        SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0x00, 0x00, 0xFF);
      }
      double entXPos, entYPos;
      std::tie(entXPos, entYPos) =
          getCenterPosition(system->m_entities[attackComp->m_targetEntID].get());

      SDL_RenderDrawLine(game->m_SDLRenderer, (int) std::round(xCenterPos),
                         (int) std::round(yCenterPos), (int) std::round(entXPos),
                         std::round(entYPos));
    }
  } else if (ent->get<TdECSShapeComponent>()->m_height == 16) {
    // draw some diagonal lines
    double x, y;
    std::tie(x, y) = getPosition(ent);

    SDL_RenderDrawLine(game->m_SDLRenderer, x + 8, y, x, y + 8);
    SDL_RenderDrawLine(game->m_SDLRenderer, x + 16, y, x, y + 16);
    SDL_RenderDrawLine(game->m_SDLRenderer, x + 16, y + 8, x + 8, y + 16);
  }

  SDL_SetRenderDrawColor(game->m_SDLRenderer, c.r, c.g, c.b, c.a);
}
