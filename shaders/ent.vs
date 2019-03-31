#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 health;

out vec3 HEALTH;

void main() {
    gl_Position.xy = vertexPosition_modelspace.xy / vec2(1600.0 / 2.0, 900.0 / 2.0);
    gl_Position.w  = 1.0;

    HEALTH = health;
}

