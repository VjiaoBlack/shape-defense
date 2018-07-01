/**
 * TdGUIGraphicsComponent.hpp
 *
 * Victor Jiao
 *
 * Enables components to be drawn (at all)
 */

#include <TdGUI/TdGUIComponents/TdGUIGraphicsComponent.hpp>
#include <TdGame.hpp>

void TdGUIGraphicsComponent::update(TdGame *game) {
  setRenderDrawColor(game->m_SDLRenderer, m_drawColor);

  SDL_RenderDrawRect(game->m_SDLRenderer, &m_rect);
}

