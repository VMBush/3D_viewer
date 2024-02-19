#version 330

layout (points) in;
layout (lines, max_vertices=31) out;

uniform bool isdashed;

void main(void)
{
    if (!isdashed) {
        gl_Position = gl_in[0].gl_Position;
        EmitVertex();
        gl_Position = gl_in[0].gl_Position;
        EmitVertex();
        EndPrimitive();
    }
    else {
        float linelen = length(vec3(gl_in[1].gl_Position - gl_in[0].gl_Position));
        int dashcount = int(min(linelen / 2, 30));
        if (dashcount % 2 == 0) {
            dashcount += 1;
        }
        float dashlen = linelen / dashcount;
        vec3 stepvec = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position) / dashcount;
        for (int i = 1; i <= dashcount; i++) {
            if (i % 2 == 1) {
                gl_Position = gl_in[0].gl_Position + stepvec * (i - 1);
                EmitVertex();
                gl_Position = gl_in[0].gl_Position + stepvec * i;
                EmitVertex();
            }
        }
        EndPrimitive();
    }
}
