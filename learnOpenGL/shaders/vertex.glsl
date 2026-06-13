#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 transform;

out vec3 ourColor;


void main()
{
    vec4 pos=transform*vec4(aPos,1.0f);
    
    gl_Position = pos;
    
    ourColor = pos.xyz;
}