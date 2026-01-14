 

#if defined(OPENGL_ES)
#extension GL_EXT_geometry_shader : enable
#extension GL_OES_geometry_shader : enable
#extension GL_EXT_geometry_point_size : enable
#endif

#define MESH_UBO

#include "glsl_ubos.h"

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

IO_LOCATION(0) in vec4 vsout_secondary[3];
IO_LOCATION(1) in vec4 vsout_norm[3];

IO_LOCATION(0) out vec4 gsout_secondary;
IO_LOCATION(1) out vec4 gsout_norm;

void main()
{
  vec4 faceEdgeA = (Mesh.invProj * gl_in[1].gl_Position) - (Mesh.invProj * gl_in[0].gl_Position);
  vec4 faceEdgeB = (Mesh.invProj * gl_in[2].gl_Position) - (Mesh.invProj * gl_in[0].gl_Position);
  vec3 faceNormal = normalize(cross(faceEdgeA.xyz, faceEdgeB.xyz));

  for(int i = 0; i < 3; i++)
  {
    gl_Position = gl_in[i].gl_Position;
    gsout_secondary = vsout_secondary[i];
    gsout_norm = vec4(faceNormal.xyz, 1);
    EmitVertex();
  }
  EndPrimitive();
}
