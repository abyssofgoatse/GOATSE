 
#pragma once

#include <stdint.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4201)
#endif

struct Vec2f
{
  Vec2f(float X, float Y)
  {
    x = X;
    y = Y;
  }
  Vec2f() { x = y = 0.0f; }

  union
  {
    struct
    {
      float x, y;
    };
    float fv[2];
  };
};

class Vec3f
{
public:
  Vec3f(const float X, const float Y, const float Z) : x(X), y(Y), z(Z) {}
  Vec3f() { x = y = z = 0.0f; }
  inline float Dot(const Vec3f &o) const { return x * o.x + y * o.y + z * o.z; }
  inline Vec3f Cross(const Vec3f &o) const
  {
    return Vec3f(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
  }

  float Length() const;
  inline void Normalise()
  {
    float l = Length();
    x /= l;
    y /= l;
    z /= l;
  }

  union
  {
    struct
    {
      float x, y, z;
    };
    float fv[3];
  };
};

struct FloatVector;

struct Vec4f
{
  Vec4f(float X, float Y, float Z, float W)
  {
    x = X;
    y = Y;
    z = Z;
    w = W;
  }
  Vec4f() { x = y = z = w = 0.0f; }
  Vec4f(const FloatVector &v);
  operator Vec3f() const { return Vec3f(x, y, z); }
  operator FloatVector() const;
  union
  {
    struct
    {
      float x, y, z, w;
    };
    float fv[4];
  };
};

inline Vec3f operator*(const Vec3f &a, const float b)
{
  return Vec3f(a.x * b, a.y * b, a.z * b);
}

inline Vec3f operator+(const Vec3f &a, const Vec3f &b)
{
  return Vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3f operator-(const Vec3f &a)
{
  return Vec3f(-a.x, -a.y, -a.z);
}

inline Vec3f operator-(const Vec3f &a, const Vec3f &b)
{
  return a + (-b);
}

inline Vec3f operator-=(Vec3f &a, const Vec3f &b)
{
  a = a - b;
  return a;
}

inline Vec3f operator+=(Vec3f &a, const Vec3f &b)
{
  a = a + b;
  return a;
}

inline Vec4f operator*(const Vec4f &a, const float b)
{
  return Vec4f(a.x * b, a.y * b, a.z * b, a.w * b);
}

inline Vec4f operator+(const Vec4f &a, const Vec4f &b)
{
  return Vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

inline Vec4f operator-(const Vec4f &a)
{
  return Vec4f(-a.x, -a.y, -a.z, -a.w);
}

inline Vec4f operator-(const Vec4f &a, const Vec4f &b)
{
  return a + (-b);
}

inline Vec4f operator-=(Vec4f &a, const Vec4f &b)
{
  a = a - b;
  return a;
}

inline Vec4f operator+=(Vec4f &a, const Vec4f &b)
{
  a = a + b;
  return a;
}

struct Vec2u
{
  Vec2u(uint32_t X, uint32_t Y)
  {
    x = X;
    y = Y;
  }
  Vec2u() { x = y = 0; }
  union
  {
    struct
    {
      uint32_t x, y;
    };
    uint32_t uv[2];
  };
};

struct Vec3u
{
  Vec3u(uint32_t X, uint32_t Y, uint32_t Z)
  {
    x = X;
    y = Y;
    z = Z;
  }
  Vec3u() { x = y = z = 0; }
  union
  {
    struct
    {
      uint32_t x, y, z;
    };
    uint32_t uv[3];
  };
};

struct Vec4u
{
  Vec4u(uint32_t X, uint32_t Y, uint32_t Z, uint32_t W)
  {
    x = X;
    y = Y;
    z = Z;
    w = W;
  }
  Vec4u() { x = y = z = w = 0; }
  union
  {
    struct
    {
      uint32_t x, y, z, w;
    };
    uint32_t uv[4];
  };
};

struct Vec3i
{
  Vec3i(int32_t X, int32_t Y, int32_t Z)
  {
    x = X;
    y = Y;
    z = Z;
  }
  Vec3i() { x = y = z = 0; }
  union
  {
    struct
    {
      int32_t x, y, z;
    };
    int32_t uv[3];
  };
};

struct Vec4i
{
  Vec4i(int32_t X, int32_t Y, int32_t Z, int32_t W)
  {
    x = X;
    y = Y;
    z = Z;
    w = W;
  }
  Vec4i() { x = y = z = w = 0; }
  union
  {
    struct
    {
      int32_t x, y, z, w;
    };
    int32_t uv[4];
  };
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif
