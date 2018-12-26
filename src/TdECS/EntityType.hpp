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
  SDL_Color c = 0x00000000;
  int w = 0;
  int h = 0;
};

template<>
struct EntityShape<EntityType::BASE> {
  SDL_Color c = {0xFF, 0xFF, 0xFF};
  int w = 48;
  int h = 48;
};


template<>
struct EntityShape<EntityType::TOWER> {
  SDL_Color c = {0xFF, 0xFF, 0xFF};
  int w = 32;
  int h = 32;
};


template<>
struct EntityShape<EntityType::WALL> {
  SDL_Color c = {0xFF, 0xFF, 0xFF};
  int w = 16;
  int h = 16;
};


template<>
struct EntityShape<EntityType::ENEMY> {
  SDL_Color c = {0xC0, 0x60, 0x60};
  int w = 16;
  int h = 16;
};
