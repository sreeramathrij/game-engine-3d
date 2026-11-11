#pragma once

#include <SDL2/SDL.h>
#include "frame_buffer.h"

// Window class to handle SDL window and rendering
class Window {
public:
  Window(int width, int height, int scale, FrameBuffer& frameBuffer);
  ~Window();
  bool init();

  bool pollEvents(int& mouseX, int& mouseY, float& cameraX, float& cameraY, float& cameraZ);
  void render();

private:
  int width, height, scale;
  FrameBuffer& frameBuffer;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
};
