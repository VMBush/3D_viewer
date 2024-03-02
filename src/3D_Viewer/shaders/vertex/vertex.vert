#version 330
layout (location = 0) in vec4 position;

uniform mat4 MVPMatrix;

void main(void)
{
    gl_Position = MVPMatrix * position;
}
