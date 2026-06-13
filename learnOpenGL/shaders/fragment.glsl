#version 330 core

out vec4 FragColor;
in vec3 ourColor;

uniform vec2 resolution;

void main()
{
    vec2 p = (gl_FragCoord.xy/resolution);
    p -= 0.5f;
    vec3 lightSource = vec3(1.0f);
    float l = dot(vec3(p,0.f),lightSource);
    FragColor = vec4(l*vec3(1.f), 1.0f);
}