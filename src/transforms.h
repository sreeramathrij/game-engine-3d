#include "math.h"

using namespace Math;

Mat4 projectionMatrix(float fFov, float fAspectRatio, float fNear, float fFar);
Mat4 translationMatrix(const Vec3& translate);
Mat4 rotationMatrix(const Vec3& rotate);
Mat4 identityMatrix();
