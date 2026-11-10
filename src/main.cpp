#include "frame_buffer.h"
#include "math.h"
#include "model.h"
#include "renderer.h"
#include "timer.h"
#include "window.h"
#include "transforms.h"

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

  /*
  std::cout << "Arguments: "<< arg << '\n';
  if(arg != 2) {
    std::cerr << "No model filepath given!" << '\n';
    return 1;
  }
  */

  std::cout << "Initializing SDL.\n";

  // defining width, height of the buffer
  const int W = 1600, H = 900;
  const int SCALE = 1; // the scale the window is to be created at

  // Initialize the frame buffer and window object
  FrameBuffer frameBuffer(W, H);
  Window window(W, H, SCALE, frameBuffer);
  if (!(window.init())) {
    return 1;
  }

  // Initialize the renderer object
  Renderer renderer(frameBuffer);
  std::cout << "SDL Initialized. \n";

  // defining the projection matrix and its parameters
  float fNear = 0.1f;
  float fFar = 1000.0f;
  float fFov = 90.0f;
  float fAspectRatio = frameBuffer.getHeight() / static_cast<float>(frameBuffer.getWidth());
  float fFovRad = 1.0f / std::tan(fFov * 0.5f * (PI / 180.0f));
  Math::Mat4 matProj = projectionMatrix(fFov, fAspectRatio, fNear, fFar);
  
  // Load the teapot mesh from the .obj file
  Mesh teapotMesh("models/utah_teapot_frank.obj");
  if (!teapotMesh.loadObjectFromFile()) {
    std::cerr << "Failed to initialize " << "models/utah_teapot_large.obj" << '!' << '\n';
    return 1;
  }

  Mesh axisMesh("models/axis.obj");
  if (!axisMesh.loadObjectFromFile()) {
    std::cerr << "Failed to initialize " << "models/axis.obj" << '!' << '\n';
    return 1;
  }

  Vec3 vCamera;

  // Create 2 teapot models with the same teapot mesh
  Model teapot(teapotMesh, renderer, vCamera, matProj);
  Model teapot2(teapotMesh, renderer, vCamera, matProj);

  Model axis(axisMesh, renderer, vCamera, matProj);

  // defining the rotation angle and its half for the teapot model transforms
  float fTheta = 2.5f;
  float fThetaBy2 = fTheta / 2.0f;

  // main loop to display window
  bool running = true;
  Uint32 then = Timer::getTick();
  Uint32 now = Timer::getTick();
  float dt = (now - then);

  // running the main loop
  while (running) {
    now = Timer::getTick();
    dt = (now - then) / 1000.0f;

    // To set the frame rate to 60 FPS, check if the delta time is greater than 1/60 seconds (0.016 seconds)
    if (dt > 0.016f) {
      // std::cout << "Delta: " << dt << '\n';
      // std::cout << "FPS: " << 1 / dt << '\n' << '\n';

      // Poll for events and check if the window is still running
      running = window.pollEvents();


      frameBuffer.clear(0xFF884488);

      // Model transformations for the teapot models
      teapot.rotate(Vec3(fThetaBy2, 0, fTheta));
      teapot.translate(Vec3(0, 0, 10));

      teapot2.rotate(Vec3(fTheta, 0, fThetaBy2));
      teapot2.translate(Vec3(5, 5, 11));

      axis.rotate(Vec3(0, 0, 0));
      axis.translate(Vec3(0, 0, 15));

      fTheta += 1.0f * dt;
      fThetaBy2 = fTheta / 2.0f;

      // Rendering the teapot models
      teapot.render();
      teapot2.render();

      axis.render();
      
      // Render the frame buffer to the window
      window.render();
      then = now;
    }
  }

  std::cout << "Quitting SDL.... \n";
  return 0;
}

