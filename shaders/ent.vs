#version 430 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 health;

out vec3 HEALTH;

layout(location = 3) uniform ivec2 griddim;
layout(location = 4) uniform vec2 windowdim;
layout(location = 5) uniform vec2 windowpos;

void main() {
    gl_Position.xy = vertexPosition_modelspace.xy / (windowdim / 2.0) + vec2(-1.0, 1.0) +  vec2(-1.0, 1.0) * windowpos / (windowdim / 2.0);

    gl_Position.w  = 1.0;

    HEALTH = health;
}

