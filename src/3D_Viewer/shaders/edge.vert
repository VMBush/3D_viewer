#version 330
layout (location = 0) in vec3 position;

uniform mat4 MVPMatrix

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * position;
}
