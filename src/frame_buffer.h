#pragma once

#include <vector>
#include <cstdint>

class FrameBuffer {
public:
  FrameBuffer(int width, int height);
  std::vector<uint32_t>& getPixels();
  const std::vector<uint32_t>& const_getPixels();
  void setPixel(int x, int y, uint32_t color);
  
  std::vector<float>& getDepths();
  const std::vector<float>& const_getDepths();
  const float getDepth(int x, int y);
  void setDepth(int x, int y, float depth);

  const int getWidth();
  const int getHeight();

  void clear(uint32_t color);

private:
  int width, height;
  std::vector<uint32_t> pixels;
  std::vector<float> depths;
};

