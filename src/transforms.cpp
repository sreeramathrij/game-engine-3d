#include "transforms.h"
#include <cmath>

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

Mat4 pointAtMatrix(Vec3& pos, Vec3& target, Vec3& up){
  Vec3 newForward = (target - pos).normalize();
  Vec3 newUp = up - (newForward * newForward.dot(up)).normalize();
  Vec3 newRight = newUp.cross(newForward);

  Mat4 pointAt;
  pointAt[0][0] = newRight.x; pointAt[0][1] = newRight.y; pointAt[0][2] = newRight.z; pointAt[0][3] = 0.0f;
  pointAt[1][0] = newUp.x; pointAt[1][1] = newUp.y; pointAt[1][2] = newUp.z; pointAt[1][3] = 0.0f;
  pointAt[2][0] = newForward.x; pointAt[2][1] = newForward.y; pointAt[2][2] = newForward.z; pointAt[2][3] = 0.0f;
  pointAt[3][0] = pos.x; pointAt[3][1] = pos.y; pointAt[3][2] = pos.z; pointAt[3][3] = 1.0f;

  return pointAt;
}

Mat4 lookAtMatrix(Mat4& pointAt) {
  Mat4 lookAt;
  lookAt[0][0] = pointAt[0][0]; lookAt[0][1] = pointAt[1][0]; lookAt[0][2] = pointAt[2][0]; lookAt[0][3] = 0.0f;
  lookAt[1][0] = pointAt[0][1]; lookAt[1][1] = pointAt[1][1]; lookAt[1][2] = pointAt[2][1]; lookAt[0][3] = 0.0f;
  lookAt[2][0] = pointAt[0][2]; lookAt[2][1] = pointAt[1][2]; lookAt[2][2] = pointAt[2][2]; lookAt[0][3] = 0.0f;
  
  lookAt[3][0] = -(pointAt[3][0] * lookAt[0][0] + pointAt[3][1] * lookAt[1][0] + pointAt[3][2] * lookAt[2][0]);
  lookAt[3][1] = -(pointAt[3][0] * lookAt[0][1] + pointAt[3][1] * lookAt[1][1] + pointAt[3][2] * lookAt[2][1]);
  lookAt[3][2] = -(pointAt[3][0] * lookAt[0][2] + pointAt[3][1] * lookAt[1][2] + pointAt[3][2] * lookAt[2][2]);

  lookAt[0][3] = 1.0f;

  return lookAt;
}
