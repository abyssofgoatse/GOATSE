 

layout(binding = 3) uniform sampler2D tex0;

layout(location = 0) out vec4 color_out;

layout(location = 0) in vec4 tex;
layout(location = 1) in vec2 glyphuv;

void main(void)
{
  float text = 0.0f;

  if(glyphuv.x >= 0.0f && glyphuv.x <= 1.0f && glyphuv.y >= 0.0f && glyphuv.y <= 1.0f)
  {
    vec2 uv;
    uv.x = mix(tex.x, tex.z, glyphuv.x);
    uv.y = mix(tex.y, tex.w, glyphuv.y);
    text = texture(tex0, uv.xy).x;
  }

  color_out = vec4(vec3(text), clamp(text + 0.5f, 0.0f, 1.0f));
}
