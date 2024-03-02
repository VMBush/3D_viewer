#version 330

layout (points) in;
layout (triangle_strip, max_vertices=365) out;

uniform float radius;

const float PI = 3.14159265358979323846;

void main(void)
{
    // проверить размерность
    vec3 center = gl_in[0].gl_Position;
    gl_Position = center;
    EmitVertex();
    float step = 2 * PI / 360;
    for (float circ = 0; circ < 2 * PI; circ += step) {
        gl_Position = vec3(center.x + radius * cos(circ), center.y + radius * sin(circ), center.z);
        EmitVertex();
    }

    gl_Position = vec3(center.x + radius, center.y, center.z);
    EmitVertex();

    EndPrimitive();

}
