#version 330

layout (points) in;
layout (triangle_strip, max_vertices=256) out;

uniform float radius;
uniform mat4 MMatrix;
uniform mat4 VPMatrix;

const float PI = 3.14159265358979323846;
uniform mat4 screenMat;


void main(void)
{
    vec4 center = MMatrix * gl_in[0].gl_Position;
    float step = 2 * PI / 30;
    for (int i = 0; i < 15; i++) {
        gl_Position = VPMatrix * center;
        EmitVertex();
        gl_Position = VPMatrix * vec4(center.x + radius * cos(2*i*step) * screenMat[0][0], center.y + radius * sin(2*i*step), center.z, 1.0);
        EmitVertex();
        gl_Position = VPMatrix * vec4(center.x + radius * cos((2*i+1)*step) * screenMat[0][0], center.y + radius * sin((2*i+1)*step), center.z, 1.0);
        EmitVertex();
    }
    gl_Position = VPMatrix * center;
    EmitVertex();
    gl_Position = VPMatrix * vec4(center.x + radius * screenMat[0][0], center.y, center.z, 1.0);
    EmitVertex();
    EndPrimitive();

}
