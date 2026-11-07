#include "transforms.h"
#include <cmath>
#include <iostream>

constexpr float PI = 3.14159265389;

Mat4 identityMatrix() {
  Mat4 result;
  result[0][0] = 1.0f;
  result[1][1] = 1.0f;
  result[2][2] = 1.0f;
  result[3][3] = 1.0f;
  return result;
}

Mat4 translationMatrix(const Vec3& translation) {
  Mat4 result;

  result[0][0] = 1.0f;
  result[1][1] = 1.0f;
  result[2][2] = 1.0f;
  result[3][3] = 1.0f;
  result[3][0] = translation.x;
  result[3][1] = translation.y;
  result[3][2] = translation.z;

  return result;
}

Mat4 rotationMatrix(const Vec3& rotation) {
  Mat4 xRot;
  Mat4 yRot;
  Mat4 zRot;

  // X Rotation Matrix
  xRot[0][0] = 1;
  xRot[1][1] = std::cos(rotation.x);
  xRot[1][2] = std::sin(rotation.x);
  xRot[2][1] = -std::sin(rotation.x);
  xRot[2][2] = std::cos(rotation.x);
  xRot[3][3] = 1;

  // Y Rotation Matrix
  yRot[0][0] = std::cos(rotation.y);
  yRot[1][1] = 1;
  yRot[0][2] = -std::sin(rotation.y);
  yRot[2][0] = std::sin(rotation.y); 
  yRot[2][2] = std::cos(rotation.y);
  yRot[3][3] = 1;


  // Z Rotation Matrix
  zRot[0][0] = std::cos(rotation.z);
  zRot[0][1] = std::sin(rotation.z);
  zRot[1][0] = -std::sin(rotation.z);
  zRot[1][1] = std::cos(rotation.z);
  zRot[2][2] = 1;
  zRot[3][3] = 1;

  
  return xRot * yRot * zRot;
}

Mat4 projectionMatrix(float fFov, float fAspectRatio, float fNear, float fFar) {
  float fFovRad = 1.0f / std::tan(fFov * 0.5f / 180.0f * PI);
  Mat4 result;
  result[0][0] = fAspectRatio * fFovRad;
  result[1][1] = fFovRad;
  result[2][2] = fFar / (fFar - fNear);
  result[3][2] = (-fFar * fNear) / (fFar - fNear);
  result[2][3] = 1.0f;
  result[3][3] = 0.0f;

  return result;
}
