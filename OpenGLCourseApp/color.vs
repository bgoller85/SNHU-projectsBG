#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec3 aNormal; // Added this line for the normal vector

out vec3 Normal;     // Output normal vector to fragment shader
out vec3 FragPos;    // Output world position to fragment shader
out vec4 fragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model*  vec4(vPos, 1.0);
    fragColor = vColor;

    FragPos = vec3(model * vec4(vPos, 1.0)); // Calculate world position
    Normal = mat3(transpose(inverse(model))) * aNormal; // Transform normal vector
}