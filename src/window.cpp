#include "window.h"
#include <iostream>

// Contructor for the Window class, initializes the window with given width, height, scale and a reference to the FrameBuffer object
WindowSDL::Window::Window(int width, int height, int scale, FrameBuffer &frameBuffer)
    : width(width), height(height), scale(scale), window(nullptr),
      renderer(nullptr), texture(nullptr), frameBuffer(frameBuffer) {}

WindowSDL::Window::~Window() {
  if (texture)
    SDL_DestroyTexture(texture);
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
  SDL_Quit();
}

// Initializes SDL, creates the window, renderer and texture
bool WindowSDL::Window::init() {
  // Initialize defaults, Video
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    std::cerr << "Could not initialize SDL: " << SDL_GetError() << '\n';
    return false;
  }
  window =
      SDL_CreateWindow("barebones", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, frameBuffer.getWidth() * scale,
                       frameBuffer.getHeight() * scale, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    std::cerr << "Could not initialize SDL: " << SDL_GetError() << '\n';
    return false;
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    std::cerr << "Could not initialize SDL: " << SDL_GetError() << '\n';
    return false;
  }

  SDL_ShowCursor(SDL_DISABLE);
  SDL_SetWindowGrab(window, SDL_TRUE);
  
  int centerX = width / 2;
  int centerY = height / 2;
  SDL_WarpMouseInWindow(window, centerX, centerY);


  // Printing the renderer information
  SDL_RendererInfo info;
  if (SDL_GetRendererInfo(renderer, &info) == 0) {
    std::cout << "SDL Renderer: " << info.name << '\n';

    std::cout << "Renderer flags: " << info.flags << '\n';

    std::cout << "Hardware accelerated: "
              << ((info.flags & SDL_RENDERER_ACCELERATED) ? "Yes" : "No")
              << '\n';

    std::cout << "VSync supported: "
              << ((info.flags & SDL_RENDERER_PRESENTVSYNC) ? "Yes" : "No")
              << '\n';
  }

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, width, height);
  if (texture == NULL) {
    std::cerr << "Could not initialize SDL: " << SDL_GetError() << '\n';
    return false;
  }
  return true;
}

// Poll events for the window, returns false if the window should close (SDL_QUIT or ESC key pressed)
int WindowSDL::Window::pollEvents(int& mouseX, int& mouseY){
  SDL_Event e;
  int poll = -1;
  while (SDL_PollEvent(&e)) {

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_W]) poll = W;
    else if(state[SDL_SCANCODE_S]) poll = S; 
    else if(state[SDL_SCANCODE_A]) poll = A;
    else if(state[SDL_SCANCODE_D]) poll = D;
    else if(state[SDL_SCANCODE_SPACE]) poll = SPACE;
    else if(state[SDL_SCANCODE_TAB]) poll = TAB;
    else if(state[SDL_SCANCODE_ESCAPE]) poll = QUIT;

    switch(e.type) {
      case SDL_MOUSEMOTION:
        mouseX = e.motion.x;
        mouseY = e.motion.y;
        poll = MOUSE_MOTION;
        break;
      case SDL_QUIT:
        poll = QUIT;
        break;
    }
  }
  return poll;
}

// Renders the current frame buffer to the window
void WindowSDL::Window::render() {
  
  SDL_UpdateTexture(texture, nullptr, frameBuffer.const_getPixels().data(),
                    frameBuffer.getWidth() * sizeof(uint32_t));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  SDL_RenderPresent(renderer);
}
