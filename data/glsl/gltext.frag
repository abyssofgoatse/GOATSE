 

uniform sampler2D font_tex;

varying vec4 tex;
varying vec2 glyphuv;

void main(void)
{
  float text = 0.0;

  if(glyphuv.x >= 0.0 && glyphuv.x <= 1.0 && glyphuv.y >= 0.0 && glyphuv.y <= 1.0)
  {
    vec2 uv;
    uv.x = mix(tex.x, tex.z, glyphuv.x);
    uv.y = mix(tex.y, tex.w, glyphuv.y);
    text = texture2D(font_tex, uv).x;
  }

  gl_FragColor = vec4(vec3(text), clamp(text + 0.5, 0.0, 1.0));
}
