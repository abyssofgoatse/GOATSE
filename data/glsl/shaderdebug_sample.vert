 

#include "glsl_globals.h"

layout(location = 0) out vec4 uvwa;

#ifdef VULKAN

layout(push_constant) uniform PushData
{
  vec4 uvwa;
  vec4 ddx;
  vec4 ddy;
}
push;

#define in_uvwa (push.uvwa)
#define in_ddx (push.ddx)
#define in_ddy (push.ddy)

#else

uniform vec4 in_uvwa;
uniform vec4 in_ddx;
uniform vec4 in_ddy;

#endif

void main(void)
{
#ifdef VULKAN
  const vec4 verts[3] = vec4[3](vec4(-0.75, -0.75, 0.5, 1.0), vec4(1.25, -0.75, 0.5, 1.0),
                                vec4(-0.75, 1.25, 0.5, 1.0));
#else
  const vec4 verts[3] =
      vec4[3](vec4(-0.75, 0.75, 0.5, 1.0), vec4(1.25, 0.75, 0.5, 1.0), vec4(-0.75, -1.25, 0.5, 1.0));
#endif

  gl_Position = verts[VERTEX_ID];
  uvwa = in_uvwa;
  if(VERTEX_ID == 1)
    uvwa.xyz += in_ddx.xyz;
  else if(VERTEX_ID == 2)
    uvwa.xyz += in_ddy.xyz;
}
