#include "frame_buffer.h"
#include <algorithm>

FrameBuffer::FrameBuffer(int width, int height) : width(width), height(height), pixels(width * height, 0xFF000000){}

std::vector<uint32_t>& FrameBuffer::getPixels() {
  return pixels;
}

const std::vector<uint32_t>& FrameBuffer::const_getPixels() {
  return pixels;
}

void FrameBuffer::setPixel(int x, int y, uint32_t color){
  if (0 <= x && x < width && 0 <= y && y < height) {
    pixels[y * width + x] = color;
  }
}

/*
void FrameBuffer::setPixels(int x, int y, int size, uint32_t color){
  std::fill(pixels.begin() + (y * width + x),  pixels.begin() + (y * width + x) + size, color);
}
*/

const int FrameBuffer::getWidth() {
  return width;
}

const int FrameBuffer::getHeight() {
  return height;
}

void FrameBuffer::clear(uint32_t color){
  std::fill(pixels.begin(), pixels.end(), color);
}

