#version 330
layout (location = 0) in vec3 position;

uniform mat4 MMatrix;
uniform mat4 VPMatrix;
uniform bool geo;

void main(void)
{
    vec4 pos = vec4(position, 1.0f);
    if (!geo) {
        pos = VPMatrix * MMatrix * pos;
    }
    gl_Position = pos;
}
