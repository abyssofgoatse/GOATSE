 

#pragma once

inline uint16_t ConvertToHalf(float comp)
{
  int *alias = (int *)&comp;
  int i = *alias;

  int sign = (i >> 16) & 0x00008000;
  int exponent = ((i >> 23) & 0x000000ff) - (127 - 15);
  int mantissa = i & 0x007fffff;

  if(exponent <= 0)
  {
    if(exponent < -10)
      return sign & 0xffff;

    mantissa |= 0x00800000;

    int t = 14 - exponent;
    int a = (1 << (t - 1)) - 1;
    int b = (mantissa >> t) & 1;

    mantissa = (mantissa + a + b) >> t;

    return (sign | mantissa) & 0xffff;
  }
  else if(exponent == 0xff - (127 - 15))
  {
    if(mantissa == 0)
      return (sign | 0x7c00) & 0xffff;

    mantissa >>= 13;
    return (sign | 0x7c00 | mantissa | (mantissa == 0)) & 0xffff;
  }
  else
  {
    mantissa = mantissa + 0x00000fff + ((mantissa >> 13) & 1);

    if(mantissa & 0x00800000)
    {
      mantissa = 0;
      exponent += 1;
    }

    if(exponent > 30)
    {
      return (sign | 0x7c00) & 0xffff;
    }

    return (sign | (exponent << 10) | (mantissa >> 13)) & 0xffff;
  }
}

inline float ConvertFromHalf(uint16_t comp)
{
  bool sign = (comp & 0x8000) != 0;
  int exponent = (comp & 0x7C00) >> 10;
  int mantissa = comp & 0x03FF;

  if(exponent == 0x00)
  {
    if(mantissa == 0)
      return sign ? -0.0f : 0.0f;

    // subnormal
    float ret = (float)mantissa;
    int *alias = (int *)&ret;

    // set sign bit and set exponent to 2^-24
    // (2^-14 from spec for subnormals * 2^-10 to convert (float)mantissa to 0.mantissa)
    *alias = (sign ? 0x80000000 : 0) | (*alias - (24 << 23));

    return ret;
  }
  else if(exponent < 0x1f)
  {
    exponent -= 15;

    float ret = 0.0f;
    int *alias = (int *)&ret;

    // convert to float. Put sign bit in the right place, convert exponent to be
    // [-128,127] and put in the right place, then shift mantissa up.
    *alias = (sign ? 0x80000000 : 0) | (exponent + 127) << 23 | (mantissa << 13);

    return ret;
  }
  else    // if(exponent = 0x1f)
  {
    union
    {
      int i;
      float f;
    } ret;

    if(mantissa == 0)
      ret.i = (sign ? 0x80000000 : 0) | 0x7F800000;
    else
      ret.i = 0x7F800001;

    return ret.f;
  }
}
