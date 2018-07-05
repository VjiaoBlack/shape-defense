#pragma once
/**
 * TdECSSystemUtils.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSSystemUtils.hpp"

#include "../TdECSComponents/TdECSPositionComponent.hpp"
#include "../TdECSComponents/TdECSShapeComponent.hpp"
#include "../TdECSComponents/TdECSTilePositionComponent.hpp"
#include "../TdECSEntity.hpp"

std::tuple<double, double> getCenterPosition(TdECSEntity *ent) {
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

std::tuple<double, double> getPosition(TdECSEntity *ent) {
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
