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
    m_rect.x = game->m_mouseX - 16;
    m_rect.y = game->m_mouseY - 16;

    m_rect.x = (m_rect.x / 16) * 16 + 0;
    m_rect.y = (m_rect.y / 16) * 16 + 2;

    SDL_SetRenderDrawColor(game->m_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRect(game->m_SDLRenderer, &m_rect);
  }
}

// right now just builds a tower
void TdConstructionManager::build(TdGame* game) {
  if (m_isOn) {
    TdECSEntity::addTower(game, game->m_entitySystem.get(), m_rect.x / 16 - 50, m_rect.y / 16 - 28);
  }
}