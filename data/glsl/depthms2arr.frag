 

#include "glsl_globals.h"

#ifdef VULKAN

layout(binding = 0) uniform PRECISION sampler2DMSArray srcDepthMS;
layout(binding = 1) uniform PRECISION usampler2DMSArray srcStencilMS;
// binding = 2 used as an image in the colour copy compute shaders

layout(push_constant) uniform multisamplePush
{
  int numMultiSamples;
  int currentSample;
  int currentSlice;
  uint currentStencil;
}
mscopy;

#define numMultiSamples (mscopy.numMultiSamples)
#define currentSample (mscopy.currentSample)
#define currentSlice (mscopy.currentSlice)
#define currentStencil (mscopy.currentStencil)

#else

uniform PRECISION sampler2DMSArray srcDepthMS;
uniform PRECISION usampler2DMSArray srcStencilMS;
// binding = 2 used as an image in the colour copy compute shaders

uniform ivec4 mscopy;

#define numMultiSamples (mscopy.x)
#define currentSample (mscopy.y)
#define currentSlice (mscopy.z)
#define currentStencil (uint(mscopy.w))

#endif

void main()
{
  ivec3 srcCoord = ivec3(int(gl_FragCoord.x), int(gl_FragCoord.y), currentSlice);

  if(currentStencil < 256u)
  {
    uint stencil = texelFetch(srcStencilMS, srcCoord, currentSample).x;

    if(stencil != currentStencil)
      discard;
  }

  gl_FragDepth = texelFetch(srcDepthMS, srcCoord, currentSample).x;
}
