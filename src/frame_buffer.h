#pragma once

#include <vector>
#include <cstdint>

class FrameBuffer {
public:
  FrameBuffer(int width, int height);
  std::vector<uint32_t>& getPixels();
  const std::vector<uint32_t>& const_getPixels();
  void setPixel(int x, int y, uint32_t color);
  
  const int getWidth();
  const int getHeight();

  void clear(uint32_t color);

private:
  int width, height;
  std::vector<uint32_t> pixels;
};
