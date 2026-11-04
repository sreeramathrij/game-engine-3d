#pragma once

#include "frame_buffer.h"
#include "math.h"

class Renderer {
public:
  Renderer(FrameBuffer& frameBuffer);

  void drawPixel(float x, float y, uint32_t color);

  void drawLine (float ax, float ay, float bx, float by, uint32_t color);

  void drawTriangle(float ax, float ay, float bx, float by, float cx, float cy, const uint32_t& color);
  void drawTriangle(const Math::Vec2& a, const Math::Vec2& b, const Math::Vec2& c, const uint32_t& color);
  
  void fillTriangle(float ax, float ay, float bx, float by, float cx, float cy, const uint32_t& color);
  void fillTriangle(const Math::Vec2& a, const Math::Vec2& b, const Math::Vec2& c, const uint32_t& color);

private:
  FrameBuffer& frameBuffer;
  int width, height;
};
