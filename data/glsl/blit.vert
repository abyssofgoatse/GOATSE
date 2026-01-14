 

#if defined(OPENGL_ES) && defined(NUM_VIEWS)
#extension GL_OVR_multiview : require
#endif

#include "glsl_globals.h"

#if defined(OPENGL_ES) && defined(NUM_VIEWS)
layout(num_views = NUM_VIEWS) in;
#endif

IO_LOCATION(0) out vec2 uv;

void main(void)
{
  const vec4 verts[4] = vec4[4](vec4(-1.0, -1.0, 0.5, 1.0), vec4(1.0, -1.0, 0.5, 1.0),
                                vec4(-1.0, 1.0, 0.5, 1.0), vec4(1.0, 1.0, 0.5, 1.0));

  gl_Position = verts[VERTEX_ID];
  uv = gl_Position.xy * 0.5f + 0.5f;
}
