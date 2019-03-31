#version 330 core

out vec3 color;

in vec3 HEALTH;

void main() {
	color = vec3(1,1,1) * HEALTH;
}