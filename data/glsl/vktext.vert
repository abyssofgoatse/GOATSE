 

#define FONT_UBO

#include "glsl_ubos.h"

layout(location = 0) out vec4 tex;
layout(location = 1) out vec2 glyphuv;

void main(void)
{
  const vec3 verts[6] = vec3[6](vec3(0.0, 0.0, 0.5), vec3(1.0, 0.0, 0.5), vec3(0.0, 1.0, 0.5),

                                vec3(1.0, 0.0, 0.5), vec3(0.0, 1.0, 0.5), vec3(1.0, 1.0, 0.5));

  uint vert = uint(gl_VertexIndex) % 6u;

  vec3 pos = verts[vert];
  uint strindex = uint(gl_VertexIndex) / 6u;

  vec2 charPos =
      vec2(float(strindex) + pos.x + general.TextPosition.x, pos.y + general.TextPosition.y);

  FontGlyphData G = glyphs.data[str.chars[strindex].x];

  gl_Position =
      vec4(charPos.xy * 2.0f * general.TextSize * general.FontScreenAspect.xy + vec2(-1, -1), 1, 1);
  glyphuv.xy = (pos.xy - G.posdata.xy) * G.posdata.zw;
  tex = G.uvdata * general.CharacterSize.xyxy;
}
