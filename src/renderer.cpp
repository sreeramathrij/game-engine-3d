#include "renderer.h"
#include <algorithm>
#include <cmath>

// Constructor for the Renderer class, initializes the frame buffer and its dimensions
Renderer::Renderer(FrameBuffer &frameBuffer)
    : frameBuffer(frameBuffer), width(frameBuffer.getWidth()),
      height(frameBuffer.getHeight()) {}

// Draws a pixel on the frame buffer at normalized screen coordinates
void Renderer::drawPixel(float x, float y, uint32_t color) {
  if (-1 <= x && x < 1 && -1 <= y && y < 1) {
    frameBuffer.setPixel(((x + 1) / 2.0f) * width,
                         height - ((y + 1) / 2.0f) * height, color);
  }
}

// Draws a line between two points using linear interpolation
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

// Draws and fills a triangle on the frame buffer to draw the triangle efficiently
void Renderer::fillTriangle(const Triangle& triangle, const uint32_t &color) {
  float aX = width * ((triangle.vertices[0].x + 1) / 2);
  float aY = (height - height * ((triangle.vertices[0].y + 1) / 2));
  float bX = width * ((triangle.vertices[1].x + 1) / 2);
  float bY = (height - height * ((triangle.vertices[1].y + 1) / 2));
  float cX = width * ((triangle.vertices[2].x + 1) / 2);
  float cY = (height - height * ((triangle.vertices[2].y + 1) / 2));

  int bbMinX = std::ceil(std::min({aX, bX, cX}) - 0.5f);
  int bbMinY = std::floor(std::min({aY, bY, cY}) - 0.5f);
  int bbMaxX = std::ceil(std::max({aX, bX, cX}) - 0.5f);
  int bbMaxY = std::floor(std::max({aY, bY, cY}) - 0.5f);
  float totalArea = Math::triangleArea(aX, aY, bX, bY, cX, cY);

  int firstX = std::max(0, (bbMinX));
  int lastX = std::min(width - 1, (bbMaxX));
  int firstY = std::max(0, (bbMinY));
  int lastY = std::min(height - 1, (bbMaxY));

  if (totalArea != 0) {
    float inverseTotalArea = 1 / totalArea;
    for (int y = firstY; y <= lastY; ++y) {
      for (float x = firstX; x <= lastX; ++x) {
        float px = x + 0.5f;
        float py = y + 0.5f;
        float alpha =
            Math::triangleArea(px, py, bX, bY, cX, cY) * inverseTotalArea;
        float beta =
            Math::triangleArea(px, py, cX, cY, aX, aY) * inverseTotalArea;
        float gamma =
            Math::triangleArea(px, py, aX, aY, bX, bY) * inverseTotalArea;

        float depth = alpha * triangle.vertices[0].z + beta * triangle.vertices[1].z + gamma * triangle.vertices[2].z;
        if ((alpha < 0 || beta < 0 || gamma < 0)) continue;
        if(depth >= frameBuffer.getDepth(x, y))
          continue;

        frameBuffer.setDepth(x, y, depth);
        frameBuffer.setPixel(x, y, color);
      }
    }
  }
}

// Draws and fills a triangle on the frame buffer to draw the triangle efficiently
void Renderer::fillTriangle(const Math::Vec3 &a, const Math::Vec3 &b,
                            const Math::Vec3 &c, const uint32_t &color) {
  float aX = width * ((a.x + 1) / 2);
  float aY = (height - height * ((a.y + 1) / 2));
  float bX = width * ((b.x + 1) / 2);
  float bY = (height - height * ((b.y + 1) / 2));
  float cX = width * ((c.x + 1) / 2);
  float cY = (height - height * ((c.y + 1) / 2));

  int bbMinX = std::ceil(std::min({aX, bX, cX}) - 0.5f);
  int bbMinY = std::floor(std::min({aY, bY, cY}) - 0.5f);
  int bbMaxX = std::ceil(std::max({aX, bX, cX}) - 0.5f);
  int bbMaxY = std::floor(std::max({aY, bY, cY}) - 0.5f);
  float totalArea = Math::triangleArea(aX, aY, bX, bY, cX, cY);

  int firstX = std::max(0, (bbMinX));
  int lastX = std::min(width - 1, (bbMaxX));
  int firstY = std::max(0, (bbMinY));
  int lastY = std::min(height - 1, (bbMaxY));

  if (totalArea != 0) {
    float inverseTotalArea = 1 / totalArea;
    for (int y = firstY; y <= lastY; ++y) {
      for (float x = firstX; x <= lastX; ++x) {
        float px = x + 0.5f;
        float py = y + 0.5f;
        float alpha =
            Math::triangleArea(px, py, bX, bY, cX, cY) * inverseTotalArea;
        float beta =
            Math::triangleArea(px, py, cX, cY, aX, aY) * inverseTotalArea;
        float gamma =
            Math::triangleArea(px, py, aX, aY, bX, bY) * inverseTotalArea;

        float depth = alpha * a.z + beta * b.z + gamma * c.z;
        if ((alpha < 0 || beta < 0 || gamma < 0)) continue;
        if(depth >= frameBuffer.getDepth(x, y))
          continue;

        frameBuffer.setDepth(x, y, depth);
        frameBuffer.setPixel(x, y, color);
      }
    }
  }
}

// Draws and fills a triangle on the frame buffer to draw the triangle efficiently
void Renderer::fillTriangle(float ax, float ay, float az, float bx, float by, float bz, float cx, 
                            float cy, float cz, const uint32_t &color) {

  float aX = width * ((ax + 1) / 2);
  float aY = (height - height * ((ay + 1) / 2));
  float bX = width * ((bx + 1) / 2);
  float bY = (height - height * ((by + 1) / 2));
  float cX = width * ((cx + 1) / 2);
  float cY = (height - height * ((cy + 1) / 2));

  int bbMinX = std::ceil(std::min({aX, bX, cX}) - 0.5f);
  int bbMinY = std::floor(std::min({aY, bY, cY}) - 0.5f);
  int bbMaxX = std::ceil(std::max({aX, bX, cX}) - 0.5f);
  int bbMaxY = std::floor(std::max({aY, bY, cY}) - 0.5f);
  float totalArea = Math::triangleArea(aX, aY, bX, bY, cX, cY);

  int firstX = std::max(0, (bbMinX));
  int lastX = std::min(width - 1, (bbMaxX));
  int firstY = std::max(0, (bbMinY));
  int lastY = std::min(height - 1, (bbMaxY));

  if (totalArea != 0) {
    float inverseTotalArea = 1 / totalArea;
    for (int y = firstY; y <= lastY; ++y) {
      for (float x = firstX; x <= lastX; ++x) {
        float px = x + 0.5f;
        float py = y + 0.5f;
        float alpha =
            Math::triangleArea(px, py, bX, bY, cX, cY) * inverseTotalArea;
        float beta =
            Math::triangleArea(px, py, cX, cY, aX, aY) * inverseTotalArea;
        float gamma =
            Math::triangleArea(px, py, aX, aY, bX, bY) * inverseTotalArea;

        float depth = alpha * az + beta * bz + gamma * cz;
        if ((alpha < 0 || beta < 0 || gamma < 0)) continue;
        if(depth >= frameBuffer.getDepth(x, y))
          continue;

        frameBuffer.setDepth(x, y, depth);
        frameBuffer.setPixel(x, y, color);
      }
    }
  }
}
