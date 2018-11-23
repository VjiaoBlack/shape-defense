/**
 * TdECSGraphicsComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "Graphics.hpp"
#include <Game.hpp>
#include <TdECS/TdECSSystems/SystemPosUtils.hpp>

#include "TdECS/Entity.hpp"

void Graphics::update(Game *game, System *system) {
  SDL_Color c;
  SDL_GetRenderDrawColor(game->m_SDLRenderer, &c.r, &c.g, &c.b, &c.a);

  auto ent = system->getEnt(m_entID);
  if (ent->has<Health>()) {
    auto healthComp = ent->get<Health>();
    SDL_SetRenderDrawColor(
        game->m_SDLRenderer, m_color.r, m_color.g, m_color.b,
        (0.2 + 0.8 * healthComp->m_curHealth / healthComp->m_maxHealth) *
            m_color.a);
  } else {
    SDL_SetRenderDrawColor(game->m_SDLRenderer, m_color.r, m_color.g, m_color.b,
                           m_color.a);
  }

  auto shape = ent->get<Shape>();
  glm::dvec2 pos = ent->getPosition();
  glm::dvec2 centerp = ent->getCenterPosition();

  SDL_Rect r{(int) std::floor(pos.x),
             (int) std::floor(pos.y),
             (int) shape->m_dimensions.x,
             (int) shape->m_dimensions.y};
  SDL_RenderDrawRect(game->m_SDLRenderer, &r);

  if (ent->has<LaserShooter>()) {
    auto attackComp = ent->get<Attack>();
    auto laserComp =
        ent->get<LaserShooter>();
    if (laserComp->m_isShooting &&
        system->getEnt(attackComp->m_targetEntID)) {
      if (ent->get<Attack>()->m_type == Attack::SHOOTER) {
        SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      } else if (ent->get<Attack>()->m_type == Attack::FIGHTER) {
        SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0x00, 0x00, 0xFF);
      }
      glm::dvec2 entp = system->getEnt(attackComp->m_targetEntID)->getCenterPosition();

      SDL_RenderDrawLine(game->m_SDLRenderer, (int) std::round(centerp.x),
                         (int) std::round(centerp.y), (int) std::round(entp.x),
                         std::round(entp.y));
    }
  } else if (ent->get<Shape>()->m_dimensions.y == 16) {
    // draw some diagonal lines
    glm::dvec2 xy = ent->getPosition();

    SDL_RenderDrawLine(game->m_SDLRenderer, xy.x + 8 , xy.y    , xy.x    , xy.y + 8 );
    SDL_RenderDrawLine(game->m_SDLRenderer, xy.x + 16, xy.y    , xy.x    , xy.y + 16);
    SDL_RenderDrawLine(game->m_SDLRenderer, xy.x + 16, xy.y + 8, xy.x + 8, xy.y + 16);
  }

  SDL_SetRenderDrawColor(game->m_SDLRenderer, c.r, c.g, c.b, c.a);
}
