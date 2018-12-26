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
  NONE,
  //// Allied
  // Attack
  BASE,
  TOWER,
  // Defense
  WALL,
  //// Enemy
  // Attack
  ENEMY
};

template<EntityType T>
struct EntityShape {
  static constexpr int w = 0;
  static constexpr int h = 0;
};

template<EntityType T>
struct EntityColor {
  static constexpr SDL_Color c = convertColorType(0x00000000);
};


template<>
struct EntityShape<EntityType::BASE> {
  static constexpr int w = 48;
  static constexpr int h = 48;
};


template<>
struct EntityShape<EntityType::TOWER> {
  static constexpr int w = 32;
  static constexpr int h = 32;
};


template<>
struct EntityShape<EntityType::WALL> {
  static constexpr int w = 16;
  static constexpr int h = 16;
};


template<>
struct EntityShape<EntityType::ENEMY> {
  static constexpr int w = 16;
  static constexpr int h = 16;
};


template<>
struct EntityColor<EntityType::BASE> {
  static constexpr SDL_Color c = convertColorType(0xFFFFFFFF);
};

template<>
struct EntityColor<EntityType::TOWER> {
  static constexpr SDL_Color c = convertColorType(0xFFFFFFFF);
};


template<>
struct EntityColor<EntityType::WALL> {
  static constexpr SDL_Color c = convertColorType(0xFFFFFFFF);
};


template<>
struct EntityColor<EntityType::ENEMY> {
  static constexpr SDL_Color c = convertColorType(0xFFC06060);
};
