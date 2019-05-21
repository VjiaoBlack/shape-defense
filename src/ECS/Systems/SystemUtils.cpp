/**
 * TdECSSystemUtils.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "SystemUtils.hpp"
#include <list>

#include "ECS/Components/Position.hpp"
#include "ECS/Components/Shape.hpp"
#include "ECS/Components/TilePosition.hpp"
#include "ECS/Entity.hpp"
#include "SystemPosUtils.hpp"

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

