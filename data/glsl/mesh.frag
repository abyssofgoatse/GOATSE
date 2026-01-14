 

#define MESH_UBO

#include "glsl_ubos.h"

// this allows overrides from outside on GL where we use name-interface matching. On vulkan we can
// default to whatever name we like

#ifndef SECONDARY_NAME
#define SECONDARY_NAME fragin_secondary
#endif

#ifndef NORM_NAME
#define NORM_NAME fragin_norm
#endif

IO_LOCATION(0) in vec4 SECONDARY_NAME;
IO_LOCATION(1) in vec4 NORM_NAME;

IO_LOCATION(0) out vec4 color_out;

void main(void)
{
  int type = Mesh.displayFormat;

  if(type == MESHDISPLAY_SECONDARY || type == MESHDISPLAY_MESHLET)
  {
    color_out = vec4(SECONDARY_NAME.xyz, 1);
  }
  else if(type == MESHDISPLAY_SECONDARY_ALPHA)
  {
    color_out = vec4(SECONDARY_NAME.www, 1);
  }
  else if(type == MESHDISPLAY_FACELIT)
  {
    vec3 lightDir = normalize(vec3(0, -0.3f, -1));

    color_out = vec4(Mesh.color.xyz * abs(dot(lightDir, NORM_NAME.xyz)), 1);
  }
  else if(type == MESHDISPLAY_EXPLODE)
  {
    vec3 lightDir = normalize(vec3(0, -0.3f, -1));

    color_out = vec4(SECONDARY_NAME.xyz * abs(dot(lightDir, NORM_NAME.xyz)), 1);
  }
  else    // if(type == MESHDISPLAY_SOLID)
  {
    color_out = vec4(Mesh.color.xyz, 1);
  }
}
