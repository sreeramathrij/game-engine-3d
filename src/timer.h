#pragma once

#include <SDL2/SDL.h>

class Timer {
public:
  static Uint32 getTick(){
    return SDL_GetTicks();
  }
};
