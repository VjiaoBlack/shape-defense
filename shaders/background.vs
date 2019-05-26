#version 430 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 vertexPosition_modelspace;
layout(location = 1) in vec2 texcoord;

out vec2 Texcoord;

// this should really just be a transformation matrix lol
layout(location = 3) uniform ivec2 griddim;
layout(location = 4) uniform vec2 windowdim;
layout(location = 5) uniform vec2 windowpos;

void main() {
    gl_Position.xy = vertexPosition_modelspace.xy;
    gl_Position.w = 1.0;

    // 0.5 to set 0, 0 to center point
    Texcoord = 0.5 + texcoord * (windowdim / (vec2(griddim) * 16.0)) + windowpos / (vec2(griddim) * 16.0);
}

