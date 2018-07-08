/**
 * TdECSShapeComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSShapeComponent.hpp"

TdECSShapeComponent::TdECSShapeComponent(double width, double height)
    : m_width(width), m_height(height) {
  m_points.push_back(glm::dvec2(0, height));
  m_points.push_back(glm::dvec2(width, height));
  m_points.push_back(glm::dvec2(width, 0));
  m_points.push_back(glm::dvec2(0, 0));
}
