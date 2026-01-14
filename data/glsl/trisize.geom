 
#if defined(OPENGL_ES)
#extension GL_EXT_geometry_shader : enable
#extension GL_OES_geometry_shader : enable
#endif

#include "glsl_globals.h"

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

IO_LOCATION(0) in vec4 vsout_secondary[3];
IO_LOCATION(1) in vec4 vsout_norm[3];

IO_LOCATION(0) out float pixarea;

BINDING(2) uniform ViewportSizeUBO
{
  vec4 size;
}
viewport;

void main()
{
  vec2 a = gl_in[0].gl_Position.xy / gl_in[0].gl_Position.w;
  vec2 b = gl_in[1].gl_Position.xy / gl_in[1].gl_Position.w;
  vec2 c = gl_in[2].gl_Position.xy / gl_in[2].gl_Position.w;

  a = (a * 0.5f + 0.5f) * viewport.size.xy;
  b = (b * 0.5f + 0.5f) * viewport.size.xy;
  c = (c * 0.5f + 0.5f) * viewport.size.xy;

  float ab = length(a - b);
  float bc = length(b - c);
  float ca = length(c - a);

  float s = (ab + bc + ca) / 2.0f;

  float area = sqrt(s * (s - ab) * (s - bc) * (s - ca));

  for(int i = 0; i < 3; i++)
  {
    gl_Position = gl_in[i].gl_Position;
    pixarea = area;
    EmitVertex();
  }
  EndPrimitive();
}
