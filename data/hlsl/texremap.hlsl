 

#include "hlsl_cbuffers.h"
#include "hlsl_texsample.h"

struct v2f
{
  float4 pos : SV_Position;
  float4 tex : TEXCOORD0;
};

float4 RENDERDOC_TexRemapFloat(v2f IN) : SV_Target0
{
  float4 ret = SampleTextureFloat4(OutputDisplayFormat & TEXDISPLAY_TYPEMASK,
                                   (ScalePS < 1 && MipLevel == 0), IN.tex.xy, Slice, MipLevel,
                                   SampleIdx, TextureResolutionPS, YUVDownsampleRate, YUVAChannels);

  ret = ((ret - RangeMinimum) * InverseRangeSize);

  return ret;
}

uint4 RENDERDOC_TexRemapUInt(v2f IN) : SV_Target0
{
  return SampleTextureUInt4(OutputDisplayFormat & TEXDISPLAY_TYPEMASK, IN.tex.xy, Slice, MipLevel,
                            SampleIdx, TextureResolutionPS);
}

int4 RENDERDOC_TexRemapSInt(v2f IN) : SV_Target0
{
  return SampleTextureInt4(OutputDisplayFormat & TEXDISPLAY_TYPEMASK, IN.tex.xy, Slice, MipLevel,
                           SampleIdx, TextureResolutionPS);
}
