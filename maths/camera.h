 

#pragma once

#include "api/replay/renderdoc_replay.h"
#include "quat.h"
#include "vec.h"

class Matrix4f;

class Camera : public ICamera
{
public:
  Camera(CameraType t) : type(t), dirty(true), pos(), dist(0.0f), angles()
  {
    Camera::ResetArcball();
  }
  virtual ~Camera() {}
  void Shutdown() { delete this; }
  void SetPosition(float x, float y, float z)
  {
    dirty = true;
    pos = Vec3f(x, y, z);
  }

  void SetNearFar(float n, float f)
  {
    m_Near = n;
    m_Far = f;
  }

  float GetNear() { return m_Near; }
  float GetFar() { return m_Far; }

  // Arcball functions
  void ResetArcball();
  void SetArcballDistance(float d)
  {
    dirty = true;
    dist = d;
  }
  void RotateArcball(float ax, float ay, float bx, float by);

  // FPS look functions
  void SetFPSRotation(float x, float y, float z)
  {
    dirty = true;
    angles = Vec3f(x, y, z);
  }

  FloatVector GetPosition();
  FloatVector GetForward();
  FloatVector GetRight();
  FloatVector GetUp();
  const Matrix4f GetMatrix();

private:
  void Update();

  CameraType type;

  bool dirty;
  Matrix4f mat, basis;

  float m_Near = 0.1f, m_Far = 100000.0f;

  Vec3f pos;

  // Arcball
  Quatf arcrot;
  float dist;

  // FPS look
  Vec3f angles;
};
