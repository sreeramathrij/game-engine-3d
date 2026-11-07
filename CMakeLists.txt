cmake_minimum_required(VERSION 3.16)
project(barebones)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

find_package(SDL2 REQUIRED)

add_executable(barebones
  src/main.cpp
  src/frame_buffer.cpp
  src/window.cpp
  src/timer.h
  src/renderer.cpp
  src/transforms.cpp
  src/math.cpp
  src/model.h
)

target_link_libraries(barebones PRIVATE SDL2::SDL2)
