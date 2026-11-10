#include "renderer.h"

class Model {
public:
  Model(const Mesh& mesh, Renderer& renderer, const Vec3& cameraPos, const Mat4& projection, Mat4& view);

  void rotate(const Vec3& rotation);
  void translate(const Vec3& translate);

  void render();

private:
  const Mesh& mesh;
  Renderer& renderer;
  const Vec3& cameraPos;
  const Mat4& projection;
  Mat4& view;
  Mat4 transform;
};
