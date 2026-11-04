#include "frame_buffer.h"
#include "math.h"
#include "model.h"
#include "renderer.h"
#include "timer.h"
#include "window.h"
#include <cstdio>
#include <iostream>
#include <utility>

constexpr uint32_t BLACK = 0xFF000000;
constexpr uint32_t WHITE = 0xFFFFFFFF;
constexpr uint32_t RED = 0xFFFF0000;
constexpr uint32_t GREEN = 0xFF00FF00;
constexpr uint32_t BLUE = 0xFF0000FF;

constexpr float PI = 3.14159265389;

void drawLine(float ax, float ay, float bx, float by, uint32_t color,
              FrameBuffer &frameBuffer);
void drawRectangle(float xPos, float yPos, int width, int height,
                   uint32_t color, FrameBuffer &frameBuffer);

int main() {
  std::cout << "Initializing SDL.\n";

  // defining width, height of the buffer
  const int W = 1000, H = 1000;
  const int SCALE = 1; // the scale the window is to be created at

  // Initialize the frame buffer and window object
  FrameBuffer frameBuffer(W, H);
  Window window(W, H, SCALE, frameBuffer);
  if (!(window.init())) {
    return 1;
  }

  Renderer renderer(frameBuffer);
  std::cout << "SDL Initialized. \n";

  float fNear = 0.1f;
  float fFar = 1000.0f;
  float fFov = 90.f;
  float fAspectRatio =
      frameBuffer.getHeight() / static_cast<float>(frameBuffer.getWidth());
  float fFovRad = 1.0f / std::tan(fFov * 0.5f * (PI / 180.0f));

  Cube cube;
  cube.init();

  Math::Mat4 matProj;
  matProj.data[0][0] = fAspectRatio * fFovRad;
  matProj.data[1][1] = fFovRad;
  matProj.data[2][2] = fFar / (fFar - fNear);
  matProj.data[3][2] = (-fFar * fNear) / (fFar - fNear);
  matProj.data[2][3] = 1.0f;

  Mat4 matRotZ, matRotX;
  float fTheta = 2.5f;
  float fThetaBy2 = fTheta / 2.0f;
  Vec3 vCamera;

  Vec3 globalLight(0.0f, 0.0f, -1.0f);

  // main loop to display window
  bool running = true;
  Uint32 then = Timer::getTick();
  Uint32 now = Timer::getTick();
  float dt = (now - then);

  // running the main loop
  while (running) {
    now = Timer::getTick();
    dt = (now - then) / 1000.0f;

    if (dt > 0.0166f) {
      std::cout << "Delta: " << dt << '\n';
      std::cout << "FPS: " << 1 / dt << '\n' << '\n';
      running = window.pollEvents();
      frameBuffer.clear(BLACK);

      fTheta += 1.0f * dt;
      fThetaBy2 = fTheta / 2.0f;

      // Z Rotation Matrix
      matRotZ.data[0][0] = std::cos(fTheta);
      matRotZ.data[0][1] = std::sin(fTheta);
      matRotZ.data[1][0] = -std::sin(fTheta);
      matRotZ.data[1][1] = std::cos(fTheta);
      matRotZ.data[2][2] = 1;
      matRotZ.data[3][3] = 1;

      // X Rotation Matrix
      matRotX.data[0][0] = 1;
      matRotX.data[1][1] = std::cos(fThetaBy2);
      matRotX.data[1][2] = std::sin(fThetaBy2);
      matRotX.data[2][1] = -std::sin(fThetaBy2);
      matRotX.data[2][2] = std::cos(fThetaBy2);
      matRotX.data[3][3] = 1;

      int triCount = 1;
      for (const auto &triangle : cube.triangles) {
        std::vector<Vec4> temp(3), points(3);
        Vec3 line1, line2;
        Vec3 normal;
        for (int i = 0; i < 3; ++i) {
          Vec4 zRotatedVertex;
          zRotatedVertex.x = triangle.vertices[i].x;
          zRotatedVertex.y = triangle.vertices[i].y;
          zRotatedVertex.z = triangle.vertices[i].z;
          zRotatedVertex.w = 1;

          // Rotation around the z axis
          zRotatedVertex = zRotatedVertex * matRotZ;

          // Rotation around the x axis
          Vec4 xRotatedVertex = zRotatedVertex * matRotX;

          // Translating the cube
          Vec4 translatedVertex = xRotatedVertex + Vec4(1, 1, 3, 0);
          points[i] = translatedVertex;

          if (i == 2) {
            line1 = points[1] - points[0];
            line2 = points[2] - points[0];

            normal = line1.cross(line2);
            normal.normalize();
          }

          Vec4 projectedVertex(translatedVertex);
          projectedVertex = projectedVertex * matProj;
          if (projectedVertex.w != 0.0f) {
            projectedVertex.x = projectedVertex.x / projectedVertex.w;
            projectedVertex.y = projectedVertex.y / projectedVertex.w;
            projectedVertex.z = projectedVertex.z / projectedVertex.w;
          }

          temp[i] = projectedVertex;
        }

        float dotProduct = normal.dot(Vec3(points[0]) - vCamera);
        

        if (dotProduct < 0) {
          float shadeDot = std::abs(globalLight.dot(normal));
          uint32_t shade = 160 * shadeDot + 96;
          shade = 0xFF000000 | (shade << 16) | (shade << 8) | (shade);
          renderer.fillTriangle(temp[0].x, temp[0].y, temp[1].x, temp[1].y,
                                temp[2].x, temp[2].y, shade);
        }
        ++triCount;
      }

      window.render();
      then = now;
    }
  }

  std::cout << "Quitting SDL.... \n";
  return 0;
}

void drawRectangle(float xPos, float yPos, int width, int height,
                   uint32_t color, FrameBuffer &frameBuffer) {
  int xPosInt = (int)xPos;
  int yPosInt = (int)yPos;
  for (int y = yPosInt; y < yPosInt + height; ++y) {
    for (int x = xPosInt; x < (xPosInt + width); ++x) {
      if (!(y == yPosInt || y == (yPosInt + height - 1))) {
        if (x == xPosInt || x == (xPosInt + (width - 1))) {
          frameBuffer.setPixel(x, y, color);
        }
      } else {
        frameBuffer.setPixel(x, y, color);
      }
    }
  }
}
