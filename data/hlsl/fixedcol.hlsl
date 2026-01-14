

#define RED 0
#define GREEN 1
#define HIGHLIGHT 2
#define WIREFRAME 3

float4 main() : SV_Target0
{
#if VARIANT == RED
  return float4(1.0f, 0.0f, 0.0f, 1.0f);
#elif VARIANT == GREEN
  return float4(0.0f, 1.0f, 0.0f, 1.0f);
#elif VARIANT == HIGHLIGHT
  return float4(0.8f, 0.1f, 0.8f, 1.0f);
#elif VARIANT == WIREFRAME
  return float4(200.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 1.0f);
#else
  return float4(1.0f, 0.0f, 1.0f, 1.0f);
#endif
}
