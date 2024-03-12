#version 330

layout (points) in;
layout (triangle_strip, max_vertices=5) out;

uniform float radius;
uniform mat4 MMatrix;
uniform mat4 VPMatrix;


void main(void)
{

    vec4 center = MMatrix * gl_in[0].gl_Position;
    vec4 vertices[4];
    vertices[0] = VPMatrix * vec4(center.x + radius, center.y + radius, center.z, center.w);
    vertices[1] = VPMatrix * vec4(center.x - radius, center.y + radius, center.z, center.w);
    vertices[2] = VPMatrix * vec4(center.x - radius, center.y - radius, center.z, center.w);
    vertices[3] = VPMatrix * vec4(center.x + radius, center.y - radius, center.z, center.w);

    for (int i = 0; i < 4; i++) {
        gl_Position = vertices[i];
        EmitVertex();
    }
    gl_Position = vertices[0];
    EmitVertex();

    EndPrimitive();

}
