/**
 * TdECSShapeComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSShapeComponent.hpp"
#include <Utils.hpp>

TdECSShapeComponent::TdECSShapeComponent(double width, double height)
    : m_width(width), m_height(height) {
  m_points.push_back(make_pair(0, height));
  m_points.push_back(make_pair(width, height));
  m_points.push_back(make_pair(width, 0));
  m_points.push_back(make_pair(0, 0));
}
