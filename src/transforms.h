#include "math.h"

using namespace Math;

// Functions to create transformation matrices
Mat4 projectionMatrix(float fFov, float fAspectRatio, float fNear, float fFar);
Mat4 translationMatrix(const Vec3& translate);
Mat4 rotationMatrix(const Vec3& rotate);
Mat4 identityMatrix();
void pointAtMatrix(Vec3& pos, Vec3& target, Vec3& up, Mat4& pointAt);
void lookAtMatrix(Mat4& pointAt, Mat4& lookAt);
