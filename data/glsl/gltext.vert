 

varying vec4 tex;
varying vec2 glyphuv;

attribute vec2 pos;
attribute vec2 uv;
attribute float charidx;

// must match defines in gl_rendertext.cpp
#define FONT_FIRST_CHAR 32
#define FONT_LAST_CHAR 126

uniform vec4 posdata[FONT_LAST_CHAR - FONT_FIRST_CHAR + 1];
uniform vec4 uvdata[FONT_LAST_CHAR - FONT_FIRST_CHAR + 1];

void main(void)
{
  vec4 glyphposdata = posdata[int(charidx)];
  vec4 glyphuvdata = uvdata[int(charidx)];

  gl_Position = vec4(pos, 1, 1);
  glyphuv.xy = (uv.xy - glyphposdata.xy) * glyphposdata.zw;
  tex = glyphuvdata;
}
