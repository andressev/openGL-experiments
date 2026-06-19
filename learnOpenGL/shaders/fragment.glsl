#version 330 core

out vec4 FragColor;
in vec3 ourColor;

uniform vec2 resolution;

void main()
{
    vec2 p = (gl_FragCoord.xy/resolution);
    p -= 0.5f;
    vec3 lightSource = vec3(1.0f);
    float l = clamp(dot(vec3(p, 0.f), lightSource),0.1f,1.0f);
    FragColor = vec4(vec3(0.f, 1.f, 1.f), 1.0f);
}