#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 transform;
uniform mat4 projection;

void main()
{
    gl_Position = projection * transform * vec4(aPos, 0.0f, 1.0f);
    //gl_Position = vec4(aPos, 0.0f, 1.0f);
}