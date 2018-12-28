#pragma once
/**
 * EntityType.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <Graphics.hpp>

enum class EntityType {
  //// Default
  NONE = 0,
  //// Allied
  // Attack
  BASE,
  TOWER,
  // Defense
  WALL,
  //// Enemy
  // Attack
  ENEMY,
  //// Count
  COUNT
};

struct entity_shape_vec_t {
  int w;
  int h;
};

constexpr entity_shape_vec_t EntityShapes[static_cast<uint>(EntityType::COUNT)+1] = {
  { 0,  0},
  {48, 48}, // BASE
  {32, 32}, // TOWER
  {16, 16}, // WALL
  {16, 16}  // ENEMY
};
constexpr uint EntityColors[static_cast<uint>(EntityType::COUNT)+1] = {
  0x00000000,
  0xFFFFFFFF, // BASE
  0xFFFFFFFF, // TOWER
  0xFFFFFFFF, // WALL
  0xFFC06060  // ENEMY
};
constexpr double EntityCosts[static_cast<uint>(EntityType::COUNT)+1] = {
    0.0,
    1000.0, // BASE
    15.0, // TOWER
    5.0, // WALL
    2.0 // ENEMY
};

template<EntityType T>
struct EntityShape {
  static constexpr int w = EntityShapes[static_cast<uint>(T)].w;
  static constexpr int h = EntityShapes[static_cast<uint>(T)].h;
};

template<EntityType T>
struct EntityColor {
  static constexpr uint c = EntityColors[static_cast<uint>(T)];
};

template<EntityType T>
struct EntityCost {
  static constexpr double c = EntityCosts[static_cast<uint>(T)];
};
