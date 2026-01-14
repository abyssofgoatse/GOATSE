 
#define CHECKER_UBO

#include "glsl_ubos.h"

// for GLES compatibility where we must match blit.vert
IO_LOCATION(0) in vec2 uv;

IO_LOCATION(0) out vec4 color_out;

void main(void)
{
  vec2 RectRelativePos = gl_FragCoord.xy - checker.RectPosition;

  // if we have a border, and our pos is inside the border, return inner color
  if(checker.BorderWidth >= 0.0f)
  {
    if(RectRelativePos.x >= checker.BorderWidth &&
       RectRelativePos.x <= checker.RectSize.x - checker.BorderWidth &&
       RectRelativePos.y >= checker.BorderWidth &&
       RectRelativePos.y <= checker.RectSize.y - checker.BorderWidth)
    {
      color_out = checker.InnerColor;
      return;
    }
  }

  vec2 ab = mod(RectRelativePos.xy, vec2(checker.CheckerSquareDimension * 2.0f));

  bool checkerVariant =
      ((ab.x < checker.CheckerSquareDimension && ab.y < checker.CheckerSquareDimension) ||
       (ab.x > checker.CheckerSquareDimension && ab.y > checker.CheckerSquareDimension));

  // otherwise return checker pattern
  color_out = checkerVariant ? checker.PrimaryColor : checker.SecondaryColor;
}
