#version 330

layout (lines) in;
layout (line_strip, max_vertices=61) out;

uniform mat4 MMatrix;
uniform mat4 VPMatrix;


void main(void)
{
    vec4 pos0 = MMatrix * gl_in[0].gl_Position;
    vec4 pos1 = MMatrix * gl_in[1].gl_Position;


    float linelen = length(vec3(pos1 - pos0));
    int dashcount = int(min(linelen / 0.05, 35));
    if (dashcount % 2 == 0) {
        dashcount += 1;
    }
    //float dashlen = linelen / dashcount;
    vec3 stepvec = vec3(pos1 - pos0) / dashcount;
    for (int i = 1; i <= dashcount; i++) {
        if (i % 2 == 1) {
            gl_Position = VPMatrix * (pos0 + vec4(stepvec * (i - 1), 0.0));
            EmitVertex();
            gl_Position = VPMatrix * (pos0 + vec4(stepvec * i, 0.0));
            EmitVertex();
            EndPrimitive();
        }
    }


}
