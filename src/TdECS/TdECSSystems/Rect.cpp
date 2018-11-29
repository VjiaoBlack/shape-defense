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
  //  intersects
  //  glm::dvec2 pa1 = this->pos;
  //  glm::dvec2 pb1 = ent->getPosition();
  //
  //  glm::dvec2 pa2 = pa1 + glm::dvec2(this->w, this->h);
  //  glm::dvec2 pb2 = pb1;
  //
  //  pb2.x += ent->get<Shape>()->m_width;
  //  pb2.y += ent->get<Shape>()->m_height;
  //
  //  if (pa1.x < pb2.x && pa2.x > pb1.x &&
  //      pa1.y > pb2.y && pa2.y < pb1.y) {
  //    return true;
  //  }
  //  return false;

  //  glm::dvec2 offset = ent->getPosition();
  //
  //  auto shapeComp = ent->get<Shape>();
  //  // clockwise
  //  glm::dvec2 pt1(pos.x, pos.y);
  //  glm::dvec2 pt2(pos.x + w, pos.y);
  //  glm::dvec2 pt3(pos.x + w, pos.y + h);
  //  glm::dvec2 pt4(pos.x, pos.y + h);
  //
  //  glm::dvec3 myRay1(pt2 - pt1, 0);
  //  glm::dvec3 myRay2(pt3 - pt2, 0);
  //  glm::dvec3 myRay3(pt4 - pt3, 0);
  //  glm::dvec3 myRay4(pt1 - pt4, 0);
  //
  //  for (auto pt : shapeComp->m_points) {
  //    pt += offset;
  //    glm::dvec3 ray1(pt - pt1, 0);
  //    glm::dvec3 ray2(pt - pt2, 0);
  //    glm::dvec3 ray3(pt - pt3, 0);
  //    glm::dvec3 ray4(pt - pt4, 0);
  //
  //    glm::dvec3 cross1 = glm::cross(myRay1, ray1);
  //    glm::dvec3 cross2 = glm::cross(myRay2, ray2);
  //    glm::dvec3 cross3 = glm::cross(myRay3, ray3);
  //    glm::dvec3 cross4 = glm::cross(myRay4, ray4);
  //
  //    if ((cross1.z > 0 && cross2.z > 0 && cross3.z > 0 && cross4.z > 0) ||
  //        (cross1.z < 0 && cross2.z < 0 && cross3.z < 0 && cross4.z < 0)) {
  //    } else {
  //      return false;
  //    }
  //  }
  //  return true;
}