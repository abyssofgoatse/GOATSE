 

#if defined(OPENGL_ES)

#extension GL_EXT_texture_cube_map_array : enable
#extension GL_EXT_texture_buffer : enable

#endif

#define TEXDISPLAY_UBO

#include "glsl_ubos.h"

#if defined(VULKAN)
#include "vk_texsample.h"
#elif defined(OPENGL_ES)
#include "gles_texsample.h"
#elif defined(OPENGL)
#include "gl_texsample.h"
#endif

// for GLES compatibility where we must match blit.vert
IO_LOCATION(0) in vec2 uv;

#if UINT_TEX
IO_LOCATION(0) out uvec4 color_out;
#elif SINT_TEX
IO_LOCATION(0) out ivec4 color_out;
#else
IO_LOCATION(0) out vec4 color_out;
#endif

void main(void)
{
  int texType = (texdisplay.OutputDisplayFormat & TEXDISPLAY_TYPEMASK);

  // calc screen co-ords with origin top left, modified by Position
  vec2 scr = gl_FragCoord.xy / texdisplay.TextureResolutionPS.xy;

#if UINT_TEX
  color_out = SampleTextureUInt4(texType, scr, texdisplay.Slice, texdisplay.MipLevel,
                                 texdisplay.SampleIdx, texdisplay.TextureResolutionPS);
#elif SINT_TEX
  color_out = SampleTextureSInt4(texType, scr, texdisplay.Slice, texdisplay.MipLevel,
                                 texdisplay.SampleIdx, texdisplay.TextureResolutionPS);
#else
  color_out = SampleTextureFloat4(texType, scr, texdisplay.Slice, texdisplay.MipLevel,
                                  texdisplay.SampleIdx, texdisplay.TextureResolutionPS,
                                  texdisplay.YUVDownsampleRate, texdisplay.YUVAChannels);

  color_out = ((color_out - texdisplay.RangeMinimum) * texdisplay.InverseRangeSize);
#endif

  if(texdisplay.Channels == vec4(1, 0, 0, 0))
  {
    color_out.y = color_out.x;
    color_out.z = color_out.x;
    color_out.w = color_out.x;
  }
  else if(texdisplay.Channels == vec4(0, 1, 0, 0))
  {
    color_out.x = color_out.y;
    color_out.z = color_out.y;
    color_out.w = color_out.y;
  }
}
