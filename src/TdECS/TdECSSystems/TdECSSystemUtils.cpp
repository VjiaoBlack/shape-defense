/**
 * TdECSSystemUtils.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <list>
#include "TdECSSystemUtils.hpp"

#include "../TdECSComponents/TdECSPositionComponent.hpp"
#include "../TdECSComponents/TdECSShapeComponent.hpp"
#include "../TdECSComponents/TdECSTilePositionComponent.hpp"
#include "../TdECSEntity.hpp"

bool TdECSRect::contains(TdECSEntity* ent) {
  double offX, offY;
  std::tie(offX, offY) = getPosition(ent);

  auto shapeComp = ent->get<TdECSShapeComponent>();
  // clockwise
  glm::dvec2 pt1(pos.x, pos.y);
  glm::dvec2 pt2(pos.x + w, pos.y);
  glm::dvec2 pt3(pos.x + w, pos.y + h);
  glm::dvec2 pt4(pos.x, pos.y + h);

  glm::dvec3 myRay1(pt2 - pt1, 0);
  glm::dvec3 myRay2(pt3 - pt2, 0);
  glm::dvec3 myRay3(pt4 - pt3, 0);
  glm::dvec3 myRay4(pt1 - pt4, 0);

  for (auto pt : shapeComp->m_points) {
    pt += glm::dvec2(offX, offY);
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

    } else {
      return false;
    }
  }
  return true;
}

// transferred from:
// https://stackoverflow.com/questions/563198/
// based on an algorithm in Andre LeMothe's
// > "Tricks of the Windows Game Programming Gurus".
bool TdECSSegment::intersects(TdECSSegment segment) {
  // double ix, iy;
  double s1x, s1y, s2x, s2y;
  s1x = p2.x - p1.x;
  s1y = p2.y - p1.y;
  s2x = segment.p2.x - segment.p1.x;
  s2y = segment.p2.y - segment.p1.y;

  double s, t;
  s = (-s1y * (p1.x - segment.p1.x) + s1x * (p1.y - segment.p1.y)) /
      (-s2x * s1y + s1x * s2y);
  t = (s2x * (p1.y - segment.p1.y) - s2y * (p1.x - segment.p1.x)) /
      (-s2x * s1y + s1x * s2y);

  if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
    // intersection
    // ix = p1.x + (t * s1x);
    // iy = p1.y + (t * s1y);
    return 1;
  }

  return 0;  // No intersection
}

std::tuple<double, double> getCenterPosition(TdECSEntity* ent) {
  if (ent->has<TdECSTilePositionComponent>()) {
    return make_tuple(ent->get<TdECSTilePositionComponent>()->m_x * 16 +
                          K_DISPLAY_SIZE_X / 2 +
                          ent->get<TdECSShapeComponent>()->m_width / 2.0,
                      ent->get<TdECSTilePositionComponent>()->m_y * 16 +
                          K_DISPLAY_SIZE_Y / 2 +
                          ent->get<TdECSShapeComponent>()->m_height / 2.0);
  } else if (ent->has<TdECSPositionComponent>()) {
    return make_tuple(ent->get<TdECSPositionComponent>()->m_x +
                          ent->get<TdECSShapeComponent>()->m_width / 2.0,
                      ent->get<TdECSPositionComponent>()->m_y +
                          ent->get<TdECSShapeComponent>()->m_height / 2.0);
  } else {
    std::string msg = "missing component: general position";
    throw TdECSMissingComponentException(msg);
  }
};

std::tuple<double, double> getPosition(TdECSEntity* ent) {
  if (ent->has<TdECSTilePositionComponent>()) {
    return make_tuple(
        ent->get<TdECSTilePositionComponent>()->m_x * 16 + K_DISPLAY_SIZE_X / 2,
        ent->get<TdECSTilePositionComponent>()->m_y * 16 +
            K_DISPLAY_SIZE_Y / 2);
  } else if (ent->has<TdECSPositionComponent>()) {
    return make_tuple(ent->get<TdECSPositionComponent>()->m_x,
                      ent->get<TdECSPositionComponent>()->m_y);
  } else {
    std::string msg = "missing component: general position";
    throw TdECSMissingComponentException(msg);
  }
};

double findCenterDistance(TdECSEntity* ent1, TdECSEntity* ent2) {
  double ent1X, ent1Y;
  std::tie(ent1X, ent1Y) = getCenterPosition(ent1);

  double ent2X, ent2Y;
  std::tie(ent2X, ent2Y) = getCenterPosition(ent2);

  return sqrt((ent1X - ent2X) * (ent1X - ent2X) +
              (ent1Y - ent2Y) * (ent1Y - ent2Y));
}

std::tuple<double, double> findCenterDisplacement(TdECSEntity* ent1,
                                                  TdECSEntity* ent2) {
  double ent1X, ent1Y;
  std::tie(ent1X, ent1Y) = getCenterPosition(ent1);

  double ent2X, ent2Y;
  std::tie(ent2X, ent2Y) = getCenterPosition(ent2);

  return make_tuple(ent2X - ent1X, ent2Y - ent1Y);
};
