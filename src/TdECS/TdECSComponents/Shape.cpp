/**
 * TdECSShapeComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "Shape.hpp"

Shape::Shape(double width, double height)
    : m_dimensions(width, height) {
}

Shape::Shape(glm::vec2 dimensions)
    : m_dimensions(dimensions) {
}

