/**
 * TdECSShapeComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSShapeComponent.hpp"
#include <Utils.hpp>

TdECSShapeComponent::TdECSShapeComponent(double width, double height) {
  m_points.push_back(make_pair<double, double>(-width / 2.0,  height / 2.0));
  m_points.push_back(make_pair<double, double>( width / 2.0,  height / 2.0));
  m_points.push_back(make_pair<double, double>( width / 2.0, -height / 2.0));
  m_points.push_back(make_pair<double, double>(-width / 2.0, -height / 2.0));
}
