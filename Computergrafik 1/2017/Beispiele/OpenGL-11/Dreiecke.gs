
#version 420 core

in VertexData {
    vec4 Color;
} VertexIn[];
out VertexData {
    vec4 Color;
} VertexOut;

layout (triangles) in;
layout (triangle_strip, max_vertices = 20) out;

void main() {}

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;
void main() {
int i;
for (i = 0; i < gl_in.length(); i++)
{gl_Position = gl_in[i].gl_Position;
VertexOut.Color=VertexIn[i].Color;
EmitVertex();}
EndPrimitive();}
