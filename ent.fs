#version 330 core

// Ouput data
out vec3 color;

in float HEALTH;


void main()
{

	// Output color = white
	color = vec3(1,1,1) * HEALTH;

}