/**
 * Graphics.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Graphics.hpp"
#include <Game.hpp>
#include <TdECS/TdECSSystems/System.hpp>
#include <Graphics.hpp>

void Graphics::update(Game* game, System* system) {
  MY_Color c;
  auto ent = system->getEnt(m_entID);

  auto shape = ent->get<Shape>();
  glm::dvec2 pos = ent->getPosition();
  glm::dvec2 centerp = ent->getCenterPosition();

  if (ent->has<LaserShooter>()) {
    auto attackComp = ent->get<Attack>();
    auto laserComp =
        ent->get<LaserShooter>();
    if (laserComp->m_isShooting &&
        system->getEnt(attackComp->m_targetEntID)) {
      if (ent->get<Attack>()->m_team == Attack::ALLIED) {
//          SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      } else if (ent->get<Attack>()->m_team == Attack::ENEMY) {
//          SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0x00, 0x00, 0xFF);
      }
      glm::dvec2 entp = system->getEnt(attackComp->m_targetEntID)->getCenterPosition();

      if (!m_validIndices) {
        m_validIndices = true;
        m_effectIndices[0] = graphicsBackend.effectVBOdata.add(centerp.x - K_DISPLAY_SIZE_X / 2.0);
        m_effectIndices[1] = graphicsBackend.effectVBOdata.add(centerp.y - K_DISPLAY_SIZE_Y / 2.0);
        m_effectIndices[2] = graphicsBackend.effectVBOdata.add(0.0);

        m_effectIndices[3] = graphicsBackend.effectVBOdata.add(entp.x - K_DISPLAY_SIZE_X / 2.0);
        m_effectIndices[4] = graphicsBackend.effectVBOdata.add(entp.y - K_DISPLAY_SIZE_Y / 2.0);
        m_effectIndices[5] = graphicsBackend.effectVBOdata.add(0);

        m_effectIndices[6] = graphicsBackend.effectVBOdata.add(centerp.x - K_DISPLAY_SIZE_X / 2.0);
        m_effectIndices[7] = graphicsBackend.effectVBOdata.add(centerp.y - K_DISPLAY_SIZE_Y / 2.0);
        m_effectIndices[8] = graphicsBackend.effectVBOdata.add(0.0);



        printf("%d...\n", graphicsBackend.effectVBOdata.m_head);
      }
    } else if (m_validIndices) {
      graphicsBackend.effectVBOdata.remove(m_effectIndices[0]);
      graphicsBackend.effectVBOdata.remove(m_effectIndices[1]);
      graphicsBackend.effectVBOdata.remove(m_effectIndices[2]);

      graphicsBackend.effectVBOdata.remove(m_effectIndices[3]);
      graphicsBackend.effectVBOdata.remove(m_effectIndices[4]);
      graphicsBackend.effectVBOdata.remove(m_effectIndices[5]);

      graphicsBackend.effectVBOdata.remove(m_effectIndices[6]);
      graphicsBackend.effectVBOdata.remove(m_effectIndices[7]);
      graphicsBackend.effectVBOdata.remove(m_effectIndices[8]);

      m_validIndices = false;
    }
  } else if (ent->get<Shape>()->m_dimensions.y == 16) {
    // draw some diagonal lines
    glm::dvec2 xy = ent->getPosition();
//      SDL_RenderDrawLine(game->m_SDLRenderer, xy.x + 8 , xy.y    , xy.x    , xy.y + 8 );
//      SDL_RenderDrawLine(game->m_SDLRenderer, xy.x + 16, xy.y    , xy.x    , xy.y + 16);
//      SDL_RenderDrawLine(game->m_SDLRenderer, xy.x + 16, xy.y + 8, xy.x + 8, xy.y + 16);
  }
}