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

  SDL_SetRenderDrawColor(game->m_SDLRenderer, m_color.r, m_color.g, m_color.b,
                         m_color.a);

  auto shape = system->m_entities[m_entId]->get<TdECSShapeComponent>();
  double xPos, yPos;
  std::tie(xPos, yPos) =
      getPosition(system->m_entities[m_entId].get());

  double xCenterPos, yCenterPos;
  std::tie(xCenterPos, yCenterPos) =
      getCenterPosition(system->m_entities[m_entId].get());

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
    auto shooterComp =
        system->m_entities[m_entId]->get<TdECSShooterComponent>();
    if (shooterComp->m_isShooting &&
        system->m_entities.count(shooterComp->m_targetEntId)) {
      SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      double entXPos, entYPos;
      std::tie(entXPos, entYPos) =
          getCenterPosition(system->m_entities[shooterComp->m_targetEntId].get());

      SDL_RenderDrawLine(game->m_SDLRenderer, (int)std::round(xCenterPos),
                         (int)std::round(yCenterPos), (int)std::round(entXPos),
                         std::round(entYPos));
    }
  }

  if (system->m_entities[m_entId]->has<TdECSFighterComponent>()) {
    auto fighterComp =
        system->m_entities[m_entId]->get<TdECSFighterComponent>();
    if (fighterComp->m_isShooting &&
        system->m_entities.count(fighterComp->m_targetEntId)) {
      SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0x00, 0x00, 0xFF);
      double entXPos, entYPos;
      std::tie(entXPos, entYPos) =
          getCenterPosition(system->m_entities[fighterComp->m_targetEntId].get());

      SDL_RenderDrawLine(game->m_SDLRenderer, (int)std::round(xCenterPos),
                         (int)std::round(yCenterPos), (int)std::round(entXPos),
                         std::round(entYPos));
    }
  }

  SDL_SetRenderDrawColor(game->m_SDLRenderer, c.r, c.g, c.b, c.a);
}
