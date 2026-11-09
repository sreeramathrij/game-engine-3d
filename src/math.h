#pragma once

// #include <cmath>
// #include <utility>
#include <vector>

namespace Math {


class Mat2;
class Mat3;
class Mat4;
class Vec2;
class Vec3;
class Vec4;

class Mat2 {
public:
  std::vector<std::vector<float>> data;

public:
  Mat2();
  Mat2(float d);
  Mat2(Mat2& mat2);

  std::vector<float>& operator[](int index);
  Mat2 operator+(Mat2& mat2);
  Mat2 operator-(Mat2& mat2);
  Mat2 operator*(Mat2& mat2);
};

class Mat3 {
public:
  std::vector<std::vector<float>> data;

public:
  Mat3();
  Mat3(float d);
  Mat3(Mat3& mat3);

  std::vector<float>& operator[](int index);
  Mat3 operator+(Mat3& mat3);
  Mat3 operator-(Mat3& mat3);
  Mat3 operator*(Mat3& mat3);
};

class Mat4 {
public:
  std::vector<std::vector<float>> data;

public:
  Mat4();
  Mat4(float d);
  Mat4(Mat4& mat4);

  std::vector<float>& operator[](int index);
  Mat4 operator+(Mat4& mat4);
  Mat4 operator-(Mat4& mat4);
  Mat4 operator*(Mat4 mat4);
};

class Vec2 {
public:
  float x, y;

public:
  Vec2();
  Vec2(float x, float y);
  Vec2(const Vec2 &vec2);
  Vec2(const Vec3 &vec3);
  Vec2(const Vec4& vec4); 

  Vec2 normalize();
  void display();

  Vec2 operator=(const Vec2& vec2);
  Vec2 operator+(const Vec2& vec2);
  Vec2 operator-(const Vec2& vec2);
  Vec2 operator*(const Mat2& mat2);
};

class Vec3 {
public:
  float x, y, z;

public:
  Vec3();
  Vec3(float x, float y, float z);
  Vec3(const Vec2 &vec2);
  Vec3(const Vec3 &vec3);
  Vec3(const Vec4& vec4); 

  Vec3 normalize();
  void display();

  Vec3 cross(const Vec3& vec3);
  float dot(const Vec3& vec3);

  Vec3 operator=(const Vec3& Vec3);
  Vec3 operator=(const Vec4& vec4); 

  Vec3 operator+(const Vec3& Vec3);
  Vec3 operator-(const Vec3& Vec3);
  Vec3 operator*(const Mat3& mat3);
};

class Vec4 {
public:
  float x, y, z, w;

public:
  Vec4();
  Vec4(float x, float y, float z, float w);
  Vec4(Vec2 &vec2);
  Vec4(Vec3 &vec3);
  Vec4(const Vec3& vec3, float w);
  Vec4(Vec4 &vec4);

  Vec4 normalize();
  void display();

  Vec4 operator=(const Vec4& Vec4);
  Vec4 operator+(const Vec4& Vec4);
  Vec4 operator-(const Vec4& Vec4);
  Vec4 operator*(const Mat4& mat4);
  Vec4 operator/(const float c);
};

float triangleArea(float ax, float ay, float bx, float by, float cx, float cy);
float intTriangleArea(int ax, int ay, int bx, int by, int cx, int cy);

float dot(const Vec3& v1, const Vec3& v2);
} // namespace Math
