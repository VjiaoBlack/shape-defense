/**
 * TdECSShapeComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSShapeComponent.hpp"

TdECSShapeComponent::TdECSShapeComponent(double width, double height)
    : m_dimensions(width, height) {
}

TdECSShapeComponent::TdECSShapeComponent(glm::vec2 dimensions)
    : m_dimensions(dimensions) {
}

