 
#include "vec.h"
#include <math.h>
#include "api/replay/data_types.h"

float Vec3f::Length() const
{
  return sqrtf(Dot(*this));
}

Vec4f::Vec4f(const FloatVector &v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
}

Vec4f::operator FloatVector() const
{
  return FloatVector(x, y, z, w);
}
