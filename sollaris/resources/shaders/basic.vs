#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 projection_view;

void main()
{
    gl_Position = projection_view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}