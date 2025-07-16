#version 330 core

in vec3 m_normal;

out vec4 fragColor;

void main(void)
{
    vec3 normal = normalize(m_normal);

    vec3 color = normal * 0.5 + 0.5;

    fragColor = vec4(color, 1.0);
}
