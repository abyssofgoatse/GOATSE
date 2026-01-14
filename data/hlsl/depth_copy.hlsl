 

Texture2D<float2> srcDepth : register(t0);
cbuffer ViewInput : register(b0)
{
  uint4 viewData;    // viewIndex, ???, ???, ???
};

void RENDERDOC_DepthCopyPS(float4 pos : SV_Position, out float depth : SV_Depth)
{
  int2 srcCoord = int2(pos.xy);
  depth = srcDepth.Load(int3(srcCoord, 0)).r;
}

Texture2DArray<float2> srcDepthArray : register(t0);

void RENDERDOC_DepthCopyArrayPS(float4 pos : SV_Position, out float depth : SV_Depth)
{
  int2 srcCoord = int2(pos.xy);
  depth = srcDepthArray.Load(int4(srcCoord, viewData.x, 0)).r;
}

Texture2DMS<float2> srcDepthMS : register(t0);

void RENDERDOC_DepthCopyMSPS(float4 pos
                             : SV_Position, uint sample
                             : SV_SampleIndex, out float depth
                             : SV_Depth)
{
  int2 srcCoord = int2(pos.xy);
  depth = srcDepthMS.Load(srcCoord, sample).r;
}

Texture2DMSArray<float2> srcDepthMSArray : register(t0);

void RENDERDOC_DepthCopyMSArrayPS(float4 pos
                                  : SV_Position, uint sample
                                  : SV_SampleIndex, out float depth
                                  : SV_Depth)
{
  int2 srcCoord = int2(pos.xy);
  depth = srcDepthMSArray.Load(int3(srcCoord, viewData.x), sample).r;
}
