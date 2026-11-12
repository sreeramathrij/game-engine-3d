#pragma once

#include "frame_buffer.h"
#include <SDL2/SDL.h>
#include <vector>

namespace WindowSDL {
enum POLL_EVENTS { QUIT, MOUSE_MOTION, W, A, S, D, SPACE, TAB };

// Window class to handle SDL window and rendering
class Window {
public:
  Window(int width, int height, int scale, FrameBuffer &frameBuffer);
  ~Window();
  bool init();

  int pollEvents(int &mouseX, int &mouseY, std::vector<int>& keysPressed);
  void render();

private:
  int width, height, scale;
  FrameBuffer &frameBuffer;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
};
} // namespace WindowSDL
