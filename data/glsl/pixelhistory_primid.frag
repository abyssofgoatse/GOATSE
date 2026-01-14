 

#include "glsl_globals.h"

IO_LOCATION(0) out vec4 color_out;

void main(void)
{
#ifdef INT_BITS_TO_FLOAT_NOT_SUPPORTED
  color_out = vec4(float(gl_PrimitiveID));
#else
  color_out = vec4(intBitsToFloat(gl_PrimitiveID));
#endif
}
