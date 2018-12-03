/** 
 * TdECSRect.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "Rect.hpp"

#include "../TdECSComponents/Shape.hpp"

bool Rect::contains(Entity *ent) {
  if (!ent) {
    LOG_ERR("Rect passed a null ent");
    return true;
  }
  if (!ent->m_alive) {
    LOG_ERR("Rect passed a dead ent. id: %d", ent->m_id);
    return true;
  }
  glm::dvec2 pa1 = this->pos;
  glm::dvec2 pb1 = ent->getPosition();

  glm::dvec2 pa2 = pa1 + glm::dvec2(this->w, this->h);
  glm::dvec2 pb2 = pb1;

  pb2 += ent->get<Shape>()->m_dimensions;

  if (pb1.x > pa1.x && pb2.x > pa1.x && pb1.x < pa2.x && pb2.x < pa2.x &&
      pb1.y > pa1.y && pb2.y > pa1.y && pb1.y < pa2.y && pb2.y < pa2.y) {
    return true;
  } else {
    return false;
  }
}