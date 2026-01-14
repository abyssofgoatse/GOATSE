 

#include "glsl_globals.h"

#if defined(VULKAN)

layout(binding = 0) uniform sampler2D srcDepth;

#else

uniform PRECISION sampler2D srcDepth;

#endif

void main()
{
  ivec2 srcCoord = ivec2(gl_FragCoord.xy);
  gl_FragDepth = texelFetch(srcDepth, srcCoord, 0).x;
}
