#version 430 core

in vec2 Texcoord;


// Ouput data
out vec4 color;

layout(location = 3) uniform ivec2 griddim;
layout(location = 4) uniform vec2 windowdim;
layout(location = 5) uniform vec2 windowpos;


layout(location = 2) uniform sampler2D tex;

void main() {
	// Output color = white
	color = vec4(vec3(float(texture(tex, Texcoord * vec2(1.0, -1.0))/ 100.0f)) * 0.2 + vec3(0.1, 0.1, 0.2), 1.0f);

	float grid = clamp(mod(gl_FragCoord.x + windowpos.x, 16), 0, 1) *
                 clamp(mod(int(windowdim.y) - gl_FragCoord.y + windowpos.y, 16), 0, 1);

	color *= vec4(vec3(grid), 1.0);
    color += vec4(0.5 * vec3(1.0 - grid), 1.0);
}