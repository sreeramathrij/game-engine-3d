#include "renderer.h"
#include <algorithm>
#include <iostream>

Renderer::Renderer(FrameBuffer &frameBuffer)
    : frameBuffer(frameBuffer), width(frameBuffer.getWidth()),
      height(frameBuffer.getHeight()) {}

void Renderer::drawPixel(float x, float y, uint32_t color) {
  if (-1 <= x && x < 1 && -1 <= y && y < 1) {
    frameBuffer.setPixel(((x + 1) / 2.0f) * width,
                         height - ((y + 1) / 2.0f) * height, color);
  }
}

void Renderer::drawLine(float ax, float ay, float bx, float by,
                        uint32_t color) {
  for (float i = 0.0f; i < 1; i += 0.002) {
    float xt = ax + (i) * (bx - ax);
    float yt = ay + (i) * (by - ay);

    drawPixel(xt, yt, color);
  }
}

void Renderer::drawTriangle(float ax, float ay, float bx, float by, float cx,
                            float cy, const uint32_t &color) {
  drawLine(ax, ay, bx, by, color);
  drawLine(bx, by, cx, cy, color);
  drawLine(cx, cy, ax, ay, color);
}

void Renderer::drawTriangle(const Math::Vec2 &a, const Math::Vec2 &b,
                            const Math::Vec2 &c, const uint32_t &color) {
  drawLine(a.x, a.y, b.x, b.y, color);
  drawLine(b.x, b.y, c.x, c.y, color);
  drawLine(c.x, c.y, a.x, a.y, color);
}

void Renderer::fillTriangle(const Math::Vec2 &a, const Math::Vec2 &b,
                            const Math::Vec2 &c, const uint32_t &color) {
  Math::Vec2 minVertex, midVertex, maxVertex;
  if (a.y < b.y) {
    if (a.y < c.y) {
      if (c.y < b.y) {
        minVertex = a;
        midVertex = c;
        maxVertex = b;
      } else {
        minVertex = a;
        midVertex = b;
        maxVertex = c;
      }
    } else {
      minVertex = c;
      midVertex = a;
      maxVertex = b;
    }
  } else {
    if (b.y < c.y) {
      if (c.y < a.y) {
        minVertex = b;
        midVertex = c;
        maxVertex = a;
      } else {
        minVertex = b;
        midVertex = a;
        maxVertex = c;
      }
    } else {
      minVertex = c;
      midVertex = b;
      maxVertex = a;
    }
  }

  if (minVertex.y == midVertex.y) {
    drawLine(minVertex.x, minVertex.y, midVertex.x, midVertex.y, color);
  } else {
    for (float i = 0; i <= 1; i += 0.001) {
      float x1 = minVertex.x + i * (midVertex.x - minVertex.x);
      float y1 = minVertex.y + i * (midVertex.y - minVertex.y);

      float x2 =
          minVertex.x + ((y1 - minVertex.y) / (maxVertex.y - minVertex.y)) *
                            (maxVertex.x - minVertex.x);
      drawLine(x1, y1, x2, y1, color);
    }
  }

  if (midVertex.y == maxVertex.y) {
    drawLine(midVertex.x, midVertex.y, maxVertex.x, maxVertex.y, color);
  } else {
    for (float i = 0; i < 1; i += 0.001) {
      float x1 = midVertex.x + i * (maxVertex.x - midVertex.x);
      float y1 = midVertex.y + i * (maxVertex.y - midVertex.y);

      float x2 =
          minVertex.x + ((y1 - minVertex.y) / (maxVertex.y - minVertex.y)) *
                            (maxVertex.x - minVertex.x);

      drawLine(x1, y1, x2, y1, color);
    }
  }
}

void Renderer::fillTriangle(float ax, float ay, float bx, float by, float cx,
                            float cy, const uint32_t &color) {
  float bbMinX = std::max(-1.0f, std::min({ax, bx, cx}));
  float bbMinY = std::max(-1.0f, std::min({ay, by, cy}));
  float bbMaxX = std::min(1.0f, std::max({ax, bx, cx}));
  float bbMaxY = std::min(1.0f, std::max({ay, by, cy}));
  float totalArea = Math::triangleArea(ax, ay, bx, by, cx, cy);

  if (totalArea != 0) {
    float inverseTotalArea = 1 / totalArea;
    for (float x = bbMinX; x <= bbMaxX; x += 0.001) {
      for (float y = bbMinY; y <= bbMaxY; y += 0.001) {
        float alpha = Math::triangleArea(x, y, bx, by, cx, cy) * inverseTotalArea;
        float beta = Math::triangleArea(x, y, cx, cy, ax, ay) * inverseTotalArea;
        float gamma = Math::triangleArea(x, y, ax, ay, bx, by) * inverseTotalArea;
        if (alpha < 0 || beta < 0 || gamma < 0)
          continue;
        drawPixel(x, y, color);
      }
    }
  }
}
