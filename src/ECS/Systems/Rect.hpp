#pragma once

/**
 * TdECSRect.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <ECS/Entity.hpp>
#include <glm/detail/type_vec3.hpp>

struct Rect {
  glm::dvec2 pos;
  double w;
  double h;

  Rect(glm::dvec2 _pos, double _w, double _h) : pos(_pos), w(_w), h(_h){};

  bool contains(Entity *ent);

  inline bool cheapIntersectsCircle(glm::dvec2 pos, double r) {
    // clockwise
    glm::dvec2 pt1(pos.x - r, pos.y - r);
    glm::dvec2 pt2(pos.x + w + r, pos.y - r);
    glm::dvec2 pt3(pos.x + w + r, pos.y + h + r);
    glm::dvec2 pt4(pos.x - r, pos.y + h + r);

    glm::dvec3 myRay1(pt2 - pt1, 0);
    glm::dvec3 myRay2(pt3 - pt2, 0);
    glm::dvec3 myRay3(pt4 - pt3, 0);
    glm::dvec3 myRay4(pt1 - pt4, 0);

    glm::dvec2 pt = pos;
    glm::dvec3 ray1(pt - pt1, 0);
    glm::dvec3 ray2(pt - pt2, 0);
    glm::dvec3 ray3(pt - pt3, 0);
    glm::dvec3 ray4(pt - pt4, 0);

    glm::dvec3 cross1 = glm::cross(myRay1, ray1);
    glm::dvec3 cross2 = glm::cross(myRay2, ray2);
    glm::dvec3 cross3 = glm::cross(myRay3, ray3);
    glm::dvec3 cross4 = glm::cross(myRay4, ray4);

    if ((cross1.z > 0 && cross2.z > 0 && cross3.z > 0 && cross4.z > 0) ||
        (cross1.z < 0 && cross2.z < 0 && cross3.z < 0 && cross4.z < 0)) {
      return true;
    } else {
      return false;
    }
  }
};
