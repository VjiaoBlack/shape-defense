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
  BOSS,
  //// Count
  COUNT
};

// TODO: instead of these "private" structs,
// consider using constexpr constructors with ECS components, and just use components.
struct entity_shape_vec_t {
  int w;
  int h;
};

struct entity_health_vec_t {
  int h;
  int a;
};

constexpr entity_shape_vec_t EntityShapes[static_cast<uint>(EntityType::COUNT)+1] = {
  { 0,  0},
  {48, 48}, // BASE
  {32, 32}, // TOWER
  {16, 16}, // WALL
  {16, 16}, // ENEMY
  {32, 32}  // BOSS
};
constexpr uint EntityColors[static_cast<uint>(EntityType::COUNT)+1] = {
  0x00000000,
  0xFFFFFFFF, // BASE
  0xFFFFFFFF, // TOWER
  0xFFFFFFFF, // WALL
  0xFFC06060, // ENEMY
  0xFFFF6060  // BOSS
};
constexpr entity_health_vec_t EntityHealths[static_cast<uint>(EntityType::COUNT)+1] = {
  {0, 0},
  {1000000, 3}, // BASE
  {100, 0}, // TOWER
  {75, 2}, // WALL
  {10, 0}, // ENEMY
  {50, 3}  // BOSS
};
constexpr double EntityCosts[static_cast<uint>(EntityType::COUNT)+1] = {
  0.0,
  1000.0, // BASE
  15.0, // TOWER
  5.0, // WALL
  2.0, // ENEMY
  10.0 // BOSS
};