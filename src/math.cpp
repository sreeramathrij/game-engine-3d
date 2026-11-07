#include "math.h"
#include <cmath>
#include <iostream>

Math::Mat2::Mat2() : data(2, std::vector<float>(2, 0)) {}
Math::Mat2::Mat2(float d) : data(2, std::vector<float>(2, d)) {}
Math::Mat2::Mat2(Mat2& mat) : data(2, std::vector<float>(2, 0)) {
  data[0][0] = mat[0][0];
  data[0][1] = mat[0][1];
  data[1][0] = mat[1][0];
  data[1][1] = mat[1][1];
}

std::vector<float>& Math::Mat2::operator[](int index) {
  return data[index];
}

Math::Mat2 Math::Mat2::operator+(Mat2& mat) {
  Mat2 result;
  result[0][0] = data[0][0] + mat[0][0];
  result[0][1] = data[0][1] + mat[0][1];
  result[1][0] = data[1][0] + mat[1][0];
  result[1][1] = data[1][1] + mat[1][1];

  return result;
}
Math::Mat2 Math::Mat2::operator-(Mat2& mat) {
  Mat2 result;
  result[0][0] = data[0][0] - mat[0][0];
  result[0][1] = data[0][1] - mat[0][1];
  result[1][0] = data[1][0] - mat[1][0];
  result[1][1] = data[1][1] - mat[1][1];

  return result;
}
Math::Mat2 Math::Mat2::operator*(Mat2& mat) {
  Mat2 result;
  result[0][0] = data[0][0] * mat[0][0] + data[0][1] * mat[1][0];
  result[0][1] = data[0][0] * mat[0][1] + data[0][1] * mat[1][1];
  result[1][0] = data[1][0] * mat[0][0] + data[1][1] * mat[1][0];
  result[1][1] = data[1][0] * mat[0][1] + data[1][1] * mat[1][1];

  return result;
}

Math::Mat3::Mat3() : data(3, std::vector<float>(3, 0)) {}
Math::Mat3::Mat3(float d) : data(3, std::vector<float>(3, d)) {}
Math::Mat3::Mat3(Mat3& mat) : data(3, std::vector<float>(3, 0)){
  data[0][0] = mat[0][0];
  data[0][1] = mat[0][1];
  data[0][2] = mat[0][2];
  data[1][0] = mat[1][0];
  data[1][1] = mat[1][1];
  data[1][2] = mat[1][2];
  data[2][0] = mat[2][0];
  data[2][1] = mat[2][1];
  data[2][2] = mat[2][2];
}

std::vector<float>& Math::Mat3::operator[](int index){
  return data[index];
}

Math::Mat3 Math::Mat3::operator+(Mat3& mat) {
  Mat3 result;
  result[0][0] = data[0][0] + mat[0][0];
  result[0][1] = data[0][1] + mat[0][1];
  result[0][2] = data[0][2] + mat[0][2];
  result[1][0] = data[1][0] + mat[1][0];
  result[1][1] = data[1][1] + mat[1][1];
  result[1][2] = data[1][2] + mat[1][2];
  result[2][0] = data[2][0] + mat[2][0];
  result[2][1] = data[2][1] + mat[2][1];
  result[2][2] = data[2][2] + mat[2][2];

  return result;
}
Math::Mat3 Math::Mat3::operator-(Mat3& mat) {
  Mat3 result;
  result[0][0] = data[0][0] - mat[0][0];
  result[0][1] = data[0][1] - mat[0][1];
  result[0][2] = data[0][2] - mat[0][2];
  result[1][0] = data[1][0] - mat[1][0];
  result[1][1] = data[1][1] - mat[1][1];
  result[1][2] = data[1][2] - mat[1][2];
  result[2][0] = data[2][0] - mat[2][0];
  result[2][1] = data[2][1] - mat[2][1];
  result[2][2] = data[2][2] - mat[2][2];

  return result;
}
Math::Mat3 Math::Mat3::operator*(Mat3& mat) {
  Mat3 result;
  result[0][0] = data[0][0] * mat[0][0] + data[0][1] * mat[1][0] + data[0][2] * mat[2][0];
  result[0][1] = data[0][0] * mat[0][1] + data[0][1] * mat[1][1] + data[0][2] * mat[2][1];
  result[0][2] = data[0][0] * mat[0][2] + data[0][1] * mat[1][2] + data[0][2] * mat[2][2];

  result[1][0] = data[1][0] * mat[0][0] + data[1][1] * mat[1][0] + data[1][2] * mat[2][0];
  result[1][1] = data[1][0] * mat[0][1] + data[1][1] * mat[1][1] + data[1][2] * mat[2][1];
  result[1][2] = data[1][0] * mat[0][2] + data[1][1] * mat[1][2] + data[1][2] * mat[2][2];

  result[2][0] = data[2][0] * mat[0][0] + data[2][1] * mat[1][0] + data[2][2] * mat[2][0];
  result[2][1] = data[2][0] * mat[0][1] + data[2][1] * mat[1][1] + data[2][2] * mat[2][1];
  result[2][2] = data[2][0] * mat[0][2] + data[2][1] * mat[1][2] + data[2][2] * mat[2][2];

  return result;
}

Math::Mat4::Mat4() : data(4, std::vector<float>(4, 0)) {}
Math::Mat4::Mat4(float d) : data(4, std::vector<float>(4, d)) {}
Math::Mat4::Mat4(Mat4& mat) : data(4, std::vector<float>(4, 0)) {
  data[0][0] = mat[0][0];
  data[0][1] = mat[0][1];
  data[0][2] = mat[0][2];
  data[0][3] = mat[0][3];
  data[1][0] = mat[1][0];
  data[1][1] = mat[1][1];
  data[1][2] = mat[1][2];
  data[1][3] = mat[1][3];
  data[2][0] = mat[2][0];
  data[2][1] = mat[2][1];
  data[2][2] = mat[2][2];
  data[2][3] = mat[2][3];
  data[3][0] = mat[3][0];
  data[3][1] = mat[3][1];
  data[3][2] = mat[3][2];
  data[3][3] = mat[3][3];
}

std::vector<float>& Math::Mat4::operator[](int index){
  return data[index];
}

Math::Mat4 Math::Mat4::operator+(Mat4& mat) {
  Mat4 result;
  result[0][0] = data[0][0] + mat[0][0];
  result[0][1] = data[0][1] + mat[0][1];
  result[0][2] = data[0][2] + mat[0][2];
  result[0][3] = data[0][3] + mat[0][3];

  result[1][0] = data[1][0] + mat[1][0];
  result[1][1] = data[1][1] + mat[1][1];
  result[1][2] = data[1][2] + mat[1][2];
  result[1][3] = data[1][3] + mat[1][3];
  
  result[2][0] = data[2][0] + mat[2][0];
  result[2][1] = data[2][1] + mat[2][1];
  result[2][2] = data[2][2] + mat[2][2];
  result[2][3] = data[2][3] + mat[2][3];

  result[3][0] = data[3][0] + mat[3][0];
  result[3][1] = data[3][1] + mat[3][1];
  result[3][2] = data[3][2] + mat[3][2];
  result[3][3] = data[3][3] + mat[3][3];

  return result;
}
Math::Mat4 Math::Mat4::operator-(Mat4& mat) {
  Mat4 result;
  result[0][0] = data[0][0] - mat[0][0];
  result[0][1] = data[0][1] - mat[0][1];
  result[0][2] = data[0][2] - mat[0][2];
  result[0][3] = data[0][3] - mat[0][3];
  
  result[1][0] = data[1][0] - mat[1][0];
  result[1][1] = data[1][1] - mat[1][1];
  result[1][2] = data[1][2] - mat[1][2];
  result[1][3] = data[1][3] - mat[1][3];

  result[2][0] = data[2][0] - mat[2][0];
  result[2][1] = data[2][1] - mat[2][1];
  result[2][2] = data[2][2] - mat[2][2];
  result[2][3] = data[2][3] - mat[2][3];

  result[3][0] = data[3][0] - mat[3][0];
  result[3][1] = data[3][1] - mat[3][1];
  result[3][2] = data[3][2] - mat[3][2];
  result[3][3] = data[3][3] - mat[3][3];

  return result;
}

Math::Mat4 Math::Mat4::operator*(Mat4 mat) {
  Mat4 result;
  result[0][0] = data[0][0] * mat[0][0] + data[0][1] * mat[1][0] + data[0][2] * mat[2][0] + data[0][3] * mat[3][0];
  result[0][1] = data[0][0] * mat[0][1] + data[0][1] * mat[1][1] + data[0][2] * mat[2][1] + data[0][3] * mat[3][1];
  result[0][2] = data[0][0] * mat[0][2] + data[0][1] * mat[1][2] + data[0][2] * mat[2][2] + data[0][3] * mat[3][2];
  result[0][3] = data[0][0] * mat[0][3] + data[0][1] * mat[1][3] + data[0][2] * mat[2][3] + data[0][3] * mat[3][3];

  result[1][0] = data[1][0] * mat[0][0] + data[1][1] * mat[1][0] + data[1][2] * mat[2][0] + data[1][3] * mat[3][0];
  result[1][1] = data[1][0] * mat[0][1] + data[1][1] * mat[1][1] + data[1][2] * mat[2][1] + data[1][3] * mat[3][1];
  result[1][2] = data[1][0] * mat[0][2] + data[1][1] * mat[1][2] + data[1][2] * mat[2][2] + data[1][3] * mat[3][2];
  result[1][3] = data[1][0] * mat[0][3] + data[1][1] * mat[1][3] + data[1][2] * mat[2][3] + data[1][3] * mat[3][3];

  result[2][0] = data[2][0] * mat[0][0] + data[2][1] * mat[1][0] + data[2][2] * mat[2][0] + data[2][3] * mat[3][0];
  result[2][1] = data[2][0] * mat[0][1] + data[2][1] * mat[1][1] + data[2][2] * mat[2][1] + data[2][3] * mat[3][1];
  result[2][2] = data[2][0] * mat[0][2] + data[2][1] * mat[1][2] + data[2][2] * mat[2][2] + data[2][3] * mat[3][2];
  result[2][3] = data[2][0] * mat[0][3] + data[2][1] * mat[1][3] + data[2][2] * mat[2][3] + data[2][3] * mat[3][3];

  result[3][0] = data[3][0] * mat[0][0] + data[3][1] * mat[1][0] + data[3][2] * mat[2][0] + data[3][3] * mat[3][0];
  result[3][1] = data[3][0] * mat[0][1] + data[3][1] * mat[1][1] + data[3][2] * mat[2][1] + data[3][3] * mat[3][1];
  result[3][2] = data[3][0] * mat[0][2] + data[3][1] * mat[1][2] + data[3][2] * mat[2][2] + data[3][3] * mat[3][2];
  result[3][3] = data[3][0] * mat[0][3] + data[3][1] * mat[1][3] + data[3][2] * mat[2][3] + data[3][3] * mat[3][3];

  return result;
}


Math::Vec2::Vec2() : x(0), y(0) {}
Math::Vec2::Vec2(float x, float y) : x(x), y(y) {}
Math::Vec2::Vec2(const Vec2 &vec2) : x(vec2.x), y(vec2.y) {}
Math::Vec2::Vec2(const Vec3 &vec3) : x(vec3.x), y(vec3.y) {}
Math::Vec2::Vec2(const Vec4 &vec4) : x(vec4.x), y(vec4.y) {}

Math::Vec2 Math::Vec2::normalize() {
  float mag = std::sqrt(x * x + y * y);
  x = x / mag;
  y = y / mag;

  return *this;
}

void Math::Vec2::display() {
  std::cout << "X: " << x << " Y: " << y << '\n';
}


Math::Vec2 Math::Vec2::operator=(const Math::Vec2 &vec2) {
  x = vec2.x;
  y = vec2.y;

  return *this;
}

Math::Vec2 Math::Vec2::operator+(const Math::Vec2 &vec2) {
  Vec2 result;
  result.x = x + vec2.x;
  result.y = y + vec2.y;

  return result;
}

Math::Vec2 Math::Vec2::operator-(const Math::Vec2 &vec2) {
  Vec2 result;
  result.x = x - vec2.x;
  result.y = y - vec2.y;

  return result;
}

Math::Vec2 Math::Vec2::operator*(const Math::Mat2 &mat2) {
  Vec2 result;
  result.x = x * mat2.data[0][0] + y * mat2.data[1][0];
  result.y = x * mat2.data[0][1] + y * mat2.data[1][1];

  return result;
}

Math::Vec3::Vec3() : x(0), y(0), z(0) {}
Math::Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
Math::Vec3::Vec3(const Vec2 &vec2) : x(vec2.x), y(vec2.y), z(0) {}
Math::Vec3::Vec3(const Vec3 &vec3) : x(vec3.x), y(vec3.y), z(vec3.z) {}
Math::Vec3::Vec3(const Vec4 &vec4) : x(vec4.x), y(vec4.y), z(vec4.z) {}

Math::Vec3 Math::Vec3::normalize() {
  float mag = std::sqrt(x * x + y * y + z * z);
  x = x / mag;
  y = y / mag;
  z = z / mag;

  return *this;
}

void Math::Vec3::display() {
  std::cout << "X: " << x << " Y: " << y << " Z: " << z << '\n';
}

Math::Vec3 Math::Vec3::cross(const Math::Vec3& vec3){
  Vec3 result;
  result.x = y * vec3.z - z * vec3.y;
  result.y = z * vec3.x - x * vec3.z;
  result.z = x * vec3.y - y * vec3.x;

  return result;
}

float Math::Vec3::dot(const Math::Vec3& vec3){
  return x * vec3.x + y * vec3.y + z * vec3.z;
}

Math::Vec3 Math::Vec3::operator=(const Math::Vec4 &vec4) {
  x = vec4.x;
  y = vec4.y;
  z = vec4.z;

  return *this;

}

Math::Vec3 Math::Vec3::operator=(const Math::Vec3 &vec3) {
  x = vec3.x;
  y = vec3.y;
  z = vec3.z;

  return *this;
}

Math::Vec3 Math::Vec3::operator+(const Math::Vec3 &vec3) {
  Vec3 result;
  result.x = x + vec3.x;
  result.y = y + vec3.y;
  result.z = z + vec3.z;

  return result;
}

Math::Vec3 Math::Vec3::operator-(const Math::Vec3 &vec3) {
  Vec3 result;
  result.x = x - vec3.x;
  result.y = y - vec3.y;
  result.z = z - vec3.z;

  return result;
}

Math::Vec3 Math::Vec3::operator*(const Math::Mat3 &mat3) {
  Vec3 result;
  result.x = x * mat3.data[0][0] + y * mat3.data[1][0] + z * mat3.data[2][0];
  result.y = x * mat3.data[0][1] + y * mat3.data[1][1] + z * mat3.data[2][1];
  result.z = x * mat3.data[0][2] + y * mat3.data[1][2] + z * mat3.data[2][2];

  return result;
}

Math::Vec4::Vec4() : x(0), y(0), z(0), w(0) {}
Math::Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
Math::Vec4::Vec4(Vec2 &vec2) : x(vec2.x), y(vec2.y), z(0), w(0) {}
Math::Vec4::Vec4(Vec3 &vec3) : x(vec3.x), y(vec3.y), z(vec3.z), w(0) {}
Math::Vec4::Vec4(const Vec3& vec3, float w) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}
Math::Vec4::Vec4(Vec4 &vec4) : x(vec4.x), y(vec4.y), z(vec4.z), w(vec4.w) {}

Math::Vec4 Math::Vec4::normalize() {
  float mag = std::sqrt(x * x + y * y + z * z + w * w);
  x = x / mag;
  y = y / mag;
  z = z / mag;
  w = w / mag;

  return *this;
}

void Math::Vec4::display() {
  std::cout << "X: " << x << " Y: " << y << " Z: " << z << " W: " << w << '\n';
}

Math::Vec4 Math::Vec4::operator=(const Math::Vec4 &vec4) {
  x = vec4.x;
  y = vec4.y;
  z = vec4.z;
  w = vec4.w;

  return *this;
}

Math::Vec4 Math::Vec4::operator+(const Math::Vec4 &vec4) {
  Vec4 result;
  result.x = x + vec4.x;
  result.y = y + vec4.y;
  result.z = z + vec4.z;
  result.w = w + vec4.w;

  return result;
}

Math::Vec4 Math::Vec4::operator-(const Math::Vec4 &vec4) {
  Vec4 result;
  result.x = x - vec4.x;
  result.y = y - vec4.y;
  result.z = z - vec4.z;
  result.w = w - vec4.w;

  return result;
}

Math::Vec4 Math::Vec4::operator*(const Math::Mat4 &mat4) {
  Vec4 result;
  result.x = x * mat4.data[0][0] + y * mat4.data[1][0] + z * mat4.data[2][0] + w * mat4.data[3][0];
  result.y = x * mat4.data[0][1] + y * mat4.data[1][1] + z * mat4.data[2][1] + w * mat4.data[3][1];
  result.z = x * mat4.data[0][2] + y * mat4.data[1][2] + z * mat4.data[2][2] + w * mat4.data[3][2];
  result.w = x * mat4.data[0][3] + y * mat4.data[1][3] + z * mat4.data[2][3] + w * mat4.data[3][3];

  return result;
}


float Math::triangleArea(float ax, float ay, float bx, float by, float cx, float cy) {
  return (ax * (by-cy) + bx * (cy-ay) + cx * (ay-by)) * 0.5;
}

float Math::intTriangleArea(int ax, int ay, int bx, int by, int cx, int cy) {
  return (ax * (by-cy) + bx * (cy-ay) + cx * (ay-by)) * 0.5f;
}
