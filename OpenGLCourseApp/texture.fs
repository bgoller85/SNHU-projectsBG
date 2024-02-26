#version 330 core

in vec2 texcoords;

out vec4 color;

uniform sampler2D texSample;

void main()
{
    color = texture(texSample, texcoords);
}