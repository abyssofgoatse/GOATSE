 
#include "glsl_globals.h"

#if defined(OPENGL_ES) && __VERSION__ == 100

// GLES shading language 1.0 must use gl_FragColor
#define color_out gl_FragColor

#else

// otherwise we use a proper output
IO_LOCATION(0) out vec4 color_out;

#endif

#ifndef VULKAN    // Vulkan uses SPIR-V patching

// if we're compiling for GL SPIR-V, give the uniform an explicit location
#ifdef GL_SPIRV
layout(location = 99)
#endif

    uniform vec4 RENDERDOC_Fixed_Color;

#endif

void main(void)
{
#ifdef VULKAN
  // used to have a shader-replacement pixel shader
  // that outputs a fixed colour, without needing a
  // slot in a descriptor set. We re-write the SPIR-V
  // on the fly to replace these constants
  color_out = vec4(1.1f, 2.2f, 3.3f, 4.4f);
#else
  color_out = RENDERDOC_Fixed_Color;
#endif
}
