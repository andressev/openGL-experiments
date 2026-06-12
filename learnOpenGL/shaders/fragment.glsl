#version 330 core

out vec4 FragColor;
in vec3 ourColor;

uniform vec2 resolution;

void main()
{
    vec2 p = (gl_FragCoord.xy/resolution);
    p -= 0.5f;
    FragColor = vec4(p,0.f,1.0f);
}