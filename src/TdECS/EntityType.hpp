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

template<class T>
struct EntityShape {
  SDL_Color c = 0x00000000;
  int w = 0;
  int h = 0;
};

template<EntityType::BASE>
struct EntityShape {
  SDL_Color c = 0xFFFFFFFF;
  int w = 48;
  int h = 48;
};


template<EntityType::TOWER>
struct EntityShape {
  SDL_Color c = 0xFFFFFFFF;
  int w = 32;
  int h = 32;
};


template<EntityType::WALL>
struct EntityShape {
  SDL_Color c = 0xFFFFFFFF;
  int w = 16;
  int h = 16;
};


template<EntityType::ENEMY>
struct EntityShape {
  SDL_Color c = 0xFFC06060;
  int w = 16;
  int h = 16;
};
