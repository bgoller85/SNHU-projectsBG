#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 2) in vec2 vTexCoord;

out vec2 texcoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// move vertex into clip space
	gl_Position = projection * view * model*  vec4(vPos, 1.0);
	texcoords = vTexCoord;
}