#include "renderer.h"
#include <algorithm>
#include <cmath>
#include <vector>

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
void Renderer::fillTriangle(Triangle& triangle, const uint32_t &color) {
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


int Renderer::triangleClipAtPlane(Vec3& planeP, Vec3& planeN, Triangle& inTri, Triangle& outTri1, Triangle& outTri2) {
  planeN = planeN.normalize();

  // Return signed shortes distance from point to plane, plane normal must be a normal vector
  auto dist = [&](Vec3& p) {
    Vec3 n = p.normalize();
    return (planeN.dot(p) - planeN.dot(planeP));
  };

  // Create 2 temporary storage arrays to classify points either side of plane
  // If distance sign is positive, point lies 'inside' the plane
  std::vector<Vec3*> insidePoints(3); int nInsidePointCount = 0;
  std::vector<Vec3*> outsidePoints(3); int nOutsidePointCount = 0;

  // Get signed distance of each point in triangle to plane
  float d0 = dist(inTri.vertices[0]);
  float d1 = dist(inTri.vertices[1]);
  float d2 = dist(inTri.vertices[2]);

  if(d0 >= 0) {
    insidePoints[nInsidePointCount++] = &inTri.vertices[0];
  } else {
    outsidePoints[nOutsidePointCount++] = &inTri.vertices[0];
  }
  
  if(d1 >= 0) {
    insidePoints[nInsidePointCount++] = &inTri.vertices[1];
  } else {
    outsidePoints[nOutsidePointCount++] = &inTri.vertices[1];
  }

  if(d2 >= 0) {
    insidePoints[nInsidePointCount++] = &inTri.vertices[2];
  } else {
    outsidePoints[nOutsidePointCount++] = &inTri.vertices[2];
  }

  if (nInsidePointCount == 0) {
    // Whole points lie outside the plane, so clip the whole triangle
    return 0;
  } else if (nInsidePointCount == 3) {
    // Whole points lie outside the plane, so clip the whole triangle
    outTri1 = inTri;
    return 1; // Return the original triangle, no clipping needed
  } else if (nInsidePointCount == 1 && nOutsidePointCount == 2) {
    // Triangle should be clipped. As two points lie outside the plane, the triangle simply becomes a smaller triangle

    outTri1.normal = inTri.normal;

    // The inside point is valid
    outTri1.vertices[0] = *insidePoints[0];

    // The two new points are at the locations where the original sides of the triangle (lines) intersect with the plane
    outTri1.vertices[1] = intersectPlane(planeP, planeN, *insidePoints[0], *outsidePoints[0]);
    outTri1.vertices[2] = intersectPlane(planeP, planeN, *insidePoints[0], *outsidePoints[1]);

    return 1;
  } else if (nInsidePointCount == 2 && nOutsidePointCount == 1) {
    // Triangle should be clipped, as two points lie inside the plane. The clipped triangle becomees a "quad"

    // Copy params into new triangles
    outTri1.normal = inTri.normal;
    outTri2.normal = inTri.normal;

    // The first triangle consists of the two inside points and a new point determined by the location where one side of the triangle intersects with the plane
    outTri1.vertices[0] = *insidePoints[0];
    outTri1.vertices[1] = *insidePoints[1];
    outTri1.vertices[2] = intersectPlane(planeP, planeN, *insidePoints[0], *outsidePoints[0]);

    // The first triangle consists of the two inside points and a new point determined by the location where one side of the triangle intersects with the plane
    outTri2.vertices[0] = *insidePoints[0];
    outTri2.vertices[1] = outTri1.vertices[2];
    outTri2.vertices[2] = intersectPlane(planeP, planeN, *insidePoints[1], *outsidePoints[0]);

    return 2;
  }

  return -1;
}
