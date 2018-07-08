#pragma once
/**
 * TdECSSystemPosUtils.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "../TdECSEntity.hpp"

inline glm::dvec2 getPosition(TdECSEntity *ent) {
  if (ent->has<TdECSTilePositionComponent>()) {
    return glm::dvec2(
        ent->get<TdECSTilePositionComponent>()->m_x * 16 + K_DISPLAY_SIZE_X / 2,
        ent->get<TdECSTilePositionComponent>()->m_y * 16 +
            K_DISPLAY_SIZE_Y / 2);
  } else if (ent->has<TdECSPositionComponent>()) {
    return glm::dvec2(ent->get<TdECSPositionComponent>()->m_x,
                      ent->get<TdECSPositionComponent>()->m_y);
  } else {
    std::string msg = "missing component: general position";
    throw TdECSMissingComponentException(msg);
  }
};

inline glm::dvec2 getCenterPosition(TdECSEntity *ent) {
  if (ent->has<TdECSTilePositionComponent>()) {
    return glm::dvec2(ent->get<TdECSTilePositionComponent>()->m_x * 16 +
                          K_DISPLAY_SIZE_X / 2 +
                          ent->get<TdECSShapeComponent>()->m_width / 2.0,
                      ent->get<TdECSTilePositionComponent>()->m_y * 16 +
                          K_DISPLAY_SIZE_Y / 2 +
                          ent->get<TdECSShapeComponent>()->m_height / 2.0);
  } else if (ent->has<TdECSPositionComponent>()) {
    return glm::dvec2(ent->get<TdECSPositionComponent>()->m_x +
                          ent->get<TdECSShapeComponent>()->m_width / 2.0,
                      ent->get<TdECSPositionComponent>()->m_y +
                          ent->get<TdECSShapeComponent>()->m_height / 2.0);
  } else {
    std::string msg = "missing component: general position";
    throw TdECSMissingComponentException(msg);
  }
};

inline double findCenterDistance(TdECSEntity *ent1, TdECSEntity *ent2) {
  glm::dvec2 ent1p = getCenterPosition(ent1);
  glm::dvec2 ent2p = getCenterPosition(ent2);

  return sqrt((ent1p.x - ent2p.x) * (ent1p.x - ent2p.x) +
              (ent1p.y - ent2p.y) * (ent1p.y - ent2p.y));
}

inline glm::dvec2 findCenterDisplacement(TdECSEntity *ent1, TdECSEntity *ent2) {
  glm::dvec2 ent1p = getCenterPosition(ent1);
  glm::dvec2 ent2p = getCenterPosition(ent2);

  return glm::dvec2(ent2p.x - ent1p.x, ent2p.y - ent1p.y);
};
