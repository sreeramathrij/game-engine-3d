#include "math.h"

using namespace Math;

// Functions to create transformation matrices
Mat4 projectionMatrix(float fFov, float fAspectRatio, float fNear, float fFar);
Mat4 translationMatrix(const Vec3& translate);
Mat4 rotationMatrix(const Vec3& rotate);
Mat4 identityMatrix();
Mat4 pointAtMatrix(const Vec3& pos, const Vec3& target, const Vec3& up);
Mat4 lookAtMatrix(Mat4& pointAt);
