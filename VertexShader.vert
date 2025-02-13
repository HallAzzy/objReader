#version 330 core

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
attribute vec3 vertex;

void main(void)
{
    gl_Position = projectionMatrix * modelViewMatrix * vec4(vertex, 1.0);
}
