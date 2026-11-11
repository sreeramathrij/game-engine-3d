#pragma once

#include "frame_buffer.h"
#include "math.h"
#include "mesh.h"

class Renderer {
public:
  Renderer(FrameBuffer& frameBuffer);

  void drawPixel(float x, float y, uint32_t color);

  void drawLine (float ax, float ay, float bx, float by, uint32_t color);

  void drawTriangle(float ax, float ay, float bx, float by, float cx, float cy, const uint32_t& color);
  void drawTriangle(const Math::Vec2& a, const Math::Vec2& b, const Math::Vec2& c, const uint32_t& color);
  
  Triangle projectTriangle(const Triangle& triangle, const Math::Mat4& projection);
  void fillTriangle(Triangle& triangle, const uint32_t& color);
  void fillTriangle(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, const uint32_t& color);
  void fillTriangle(const Math::Vec3& a, const Math::Vec3& b, const Math::Vec3& c, const uint32_t& color);
  int triangleClipAtPlane(Vec3& planeP, Vec3& planeN, Triangle& inTri, Triangle& outTri1, Triangle& outTri2);

public:
  int width, height;
private:
  FrameBuffer& frameBuffer;
};
