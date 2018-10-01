/**
 * TdECSGraphicsComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSGraphicsComponent.hpp"
#include <TdGame.hpp>
#include <TdECS/TdECSSystems/TdECSSystemPosUtils.hpp>

#include "../TdECSEntity.hpp"

void TdECSGraphicsComponent::update(TdGame *game, TdECSSystem *system) {
  SDL_Color c;
  SDL_GetRenderDrawColor(game->m_SDLRenderer, &c.r, &c.g, &c.b, &c.a);

  auto ent = system->getEnt(m_entID);
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
  glm::dvec2 pos = ent->getPosition();
  glm::dvec2 centerp = ent->getCenterPosition();

  SDL_Rect r{(int)std::round(pos.x), (int)std::round(pos.y), (int) shape->m_width,
      (int) shape->m_height};
  SDL_RenderDrawRect(game->m_SDLRenderer, &r);

  // Disabled drawing by points
//  for (int i = 0; i < shape->m_points.size() - 1; i++) {
//    SDL_RenderDrawLine(game->m_SDLRenderer,
//                       (int) std::round(pos.x + shape->m_points[i].x),
//                       (int) std::round(pos.y + shape->m_points[i].y),
//                       (int) std::round(pos.x + shape->m_points[i + 1].x),
//                       (int) std::round(pos.y + shape->m_points[i + 1].y));
//  }
//
//  SDL_RenderDrawLine(game->m_SDLRenderer,
//                     (int) std::round(pos.x + shape->m_points.front().x),
//                     (int) std::round(pos.y + shape->m_points.front().y),
//                     (int) std::round(pos.x + shape->m_points.back().x),
//                     (int) std::round(pos.y + shape->m_points.back().y) - 1);

  if (ent->has<TdECSLaserShooterComponent>()) {
    auto attackComp = ent->get<TdECSAttackComponent>();
    auto laserComp =
        ent->get<TdECSLaserShooterComponent>();
    if (laserComp->m_isShooting &&
        system->getEnt(attackComp->m_targetEntID)) {
      if (ent->has<TdECSShooterComponent>()) {
        SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      } else if (ent->has<TdECSFighterComponent>()) {
        SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0x00, 0x00, 0xFF);
      }
      glm::dvec2 entp = system->getEnt(attackComp->m_targetEntID)->getCenterPosition();

      SDL_RenderDrawLine(game->m_SDLRenderer, (int) std::round(centerp.x),
                         (int) std::round(centerp.y), (int) std::round(entp.x),
                         std::round(entp.y));
    }
  } else if (ent->get<TdECSShapeComponent>()->m_height == 16) {
    // draw some diagonal lines
    glm::dvec2 xy = ent->getPosition();

    SDL_RenderDrawLine(game->m_SDLRenderer, xy.x + 8 , xy.y    , xy.x    , xy.y + 8 );
    SDL_RenderDrawLine(game->m_SDLRenderer, xy.x + 16, xy.y    , xy.x    , xy.y + 16);
    SDL_RenderDrawLine(game->m_SDLRenderer, xy.x + 16, xy.y + 8, xy.x + 8, xy.y + 16);
  }

  SDL_SetRenderDrawColor(game->m_SDLRenderer, c.r, c.g, c.b, c.a);
}
