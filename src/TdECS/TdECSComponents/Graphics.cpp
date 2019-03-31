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
    // handle displaying laser
    auto attackComp = ent->get<Attack>();
    auto laserComp  = ent->get<LaserShooter>();

    if (laserComp->m_isShooting &&
        system->getEnt(attackComp->m_targetEntID)) {
      // if the laser is being shot
      
      glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
      if (ent->get<Attack>()->m_team == Attack::ENEMY) {
        color = glm::vec3(1.0, 0.0, 0.0);
      }
      glm::dvec2 entp = system->getEnt(attackComp->m_targetEntID)->getCenterPosition();

      if (!m_validIndices) {
        m_validIndices = true;
        m_laser = Triangle(&graphicsBackend.effectVBOdata,
                           &graphicsBackend.effectcolorVBOdata,
                           centerp, entp, centerp,
                           color);
      } else {
        m_laser.update(centerp, entp, centerp, color);
      }
    } else if (m_validIndices) {
      m_laser.destroy();
      m_validIndices = false;
    }
  } else if (ent->get<Shape>()->m_dimensions.y == 16) {
    glm::dvec2 xy = ent->getPosition();
  }
}