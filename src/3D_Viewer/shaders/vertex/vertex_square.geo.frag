#version 330

layout (points) in;
layout (triangle_strip, max_vertices=365) out;

uniform float radius;

void main(void)
{
    // проверить размерность
    vec3 center = gl_in[0].gl_Position;
    vec3 vertices[4];
    vertices[0] = vec3(center.x + radius, center.y + radius, center.z);
    vertices[1] = vec3(center.x - radius, center.y + radius, center.z);
    vertices[2] = vec3(center.x - radius, center.y - radius, center.z);
    vertices[3] = vec3(center.x + radius, center.y - radius, center.z);

    for (int i = 0; i < 4; i++) {
        gl_Position = vertices[i];
        EmitVertex();

    }
    EndPrimitive();

}
