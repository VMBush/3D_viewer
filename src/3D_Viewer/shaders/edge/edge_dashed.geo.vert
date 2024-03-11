#version 330

layout (lines) in;
layout (line_strip, max_vertices=61) out;


void main(void)
{
    float linelen = length(vec3(gl_in[1].gl_Position - gl_in[0].gl_Position));
    int dashcount = int(max(linelen / 0.05, 5));
    if (dashcount % 2 == 0) {
        dashcount += 1;
    }
    //float dashlen = linelen / dashcount;
    vec3 stepvec = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position) / dashcount;
    for (int i = 1; i <= dashcount; i++) {
        if (i % 2 == 1) {
            gl_Position = gl_in[0].gl_Position + vec4(stepvec * (i - 1), 1.0);
            EmitVertex();
            gl_Position = gl_in[0].gl_Position + vec4(stepvec * i, 1.0);
            EmitVertex();
            EndPrimitive();
        }
    }


}
