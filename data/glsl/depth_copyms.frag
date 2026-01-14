 

#if defined(GLES)
#extension GL_OES_sample_variables : require
#elif defined(OPENGL_CORE)
#extension GL_ARB_sample_shading : require
#endif

#include "glsl_globals.h"

#if defined(VULKAN)

layout(binding = 0) uniform sampler2DMS srcDepth;

#else

uniform PRECISION sampler2DMS srcDepth;

#endif

void main()
{
  ivec2 srcCoord = ivec2(gl_FragCoord.xy);
  gl_FragDepth = texelFetch(srcDepth, srcCoord, gl_SampleID).x;
}
