 

#include "glsl_globals.h"

IO_LOCATION(0) in float pixarea;

IO_LOCATION(0) out vec4 color_out;

void main(void)
{
  float area = max(pixarea, 0.001f);
  color_out = vec4(area, area, area, 1.0f);
}
