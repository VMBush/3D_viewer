#version 330
layout (location = 0) in vec3 position;

uniform mat4 MVPMatrix;

void main(void)
{
    vec4 pos = vec4(position, 1.0f);
    gl_Position = MVPMatrix * pos;
}
