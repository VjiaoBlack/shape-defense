/** 
 * TdConstructionManager.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "../TdECS/TdECSEntity.hpp"
#include "TdConstructionManager.hpp"
#include "../TdGame.hpp"

void TdConstructionManager::update(TdGame* game) {
  if (m_isOn) {
    m_rect.x = game->m_mouseX - 17;
    m_rect.y = game->m_mouseY - 17;

    m_rect.x = (m_rect.x / 17) * 17 + 2;
    m_rect.y = (m_rect.y / 17) * 17 + 9;

    SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRect(game->m_SDLRenderer, &m_rect);


  }
  if (m_cooldown > 0) {
    m_cooldown--;
  }
}

// right now just builds a tower
void TdConstructionManager::build(TdGame* game) {
  if (m_isOn && m_cooldown == 0) {
    printf("ADDED\n");
    m_cooldown = 60;
    TdECSEntity::addTower(game, game->m_entitySystem.get(), m_rect.x / 17 - 46, m_rect.y / 17 - 25);
  }
}