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
  float data[2][2];

public:
  Mat2();
  Mat2(float d);
  Mat2(Mat2& mat2);

  Mat2 operator+(Mat2& mat2);
  Mat2 operator-(Mat2& mat2);
  Mat2 operator*(Mat2& mat2);
};

class Mat3 {
public:
  float data[3][3];

public:
  Mat3();
  Mat3(float d);
  Mat3(Mat3& mat3);

  Mat3 operator+(Mat3& mat3);
  Mat3 operator-(Mat3& mat3);
  Mat3 operator*(Mat3& mat3);
};

class Mat4 {
public:
  float data[4][4];

public:
  Mat4();
  Mat4(float d);
  Mat4(Mat4& mat4);

  Mat4 operator+(Mat4& mat4);
  Mat4 operator-(Mat4& mat4);
  Mat4 operator*(Mat4& mat4);
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

  void normalize();
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

  void normalize();
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
  Vec4(Vec4 &vec4);

  void normalize();
  void display();

  Vec4 operator=(const Vec4& Vec4);
  Vec4 operator+(const Vec4& Vec4);
  Vec4 operator-(const Vec4& Vec4);
  Vec4 operator*(const Mat4& mat4);
};

float triangleArea(float ax, float ay, float bx, float by, float cx, float cy);

} // namespace Math
