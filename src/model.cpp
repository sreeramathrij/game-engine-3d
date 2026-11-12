#include "model.h"
#include "transforms.h"

Model::Model(const Mesh &mesh, Renderer &renderer, const Vec3 &cameraPos,
             const Mat4 &projection, Mat4 &view)
    : mesh(mesh), renderer(renderer), cameraPos(cameraPos),
      projection(projection), view(view), transform(identityMatrix()) {}

// Rotates the model by multiplying the current transformation matrix with a
// rotation matrix
void Model::rotate(const Vec3 &rotation) {
  transform = transform * rotationMatrix(rotation);
}

// Translates the model by multiplying the current transformation matrix with a
// translation matrix
void Model::translate(const Vec3 &translation) {
  transform = transform * translationMatrix(translation);
}

// Renders the model by transforming then projecting each triangle to screen
// space
void Model::render() {
  Vec3 top(0.0f, -1.0f, 0.0f), topNormal(0.0f, 1.0f, 0.0f);
  Vec3 bottom(0.0f, 1.0f, 0.0f), bottomNormal(0.0f, -1.0f, 0.0f);
  Vec3 left(-1.0f, 0.0f, 0.0f), leftNormal(1.0f, 0.0f, 0.0f);
  Vec3 right(1.0f, 0.0f, 0.0f), rightNormal(-1.0f, 0.0f, 0.0f);

  std::vector<Triangle> toRender;

  for (auto triangle : mesh.triangles) {

    Triangle transformedTriangle(triangle.getTransformedTriangle(transform));

    Triangle viewedTriangle(transformedTriangle.getViewedTriangle(view));

    int nClippedTriangles = 0;
    Triangle clipped[2];

    Vec3 nearPlane(0.0f, 0.0f, 0.1f);
    Vec3 nearPlaneNormal(0.0f, 0.0f, 1.0f);
    nClippedTriangles = renderer.triangleClipAtPlane(
        nearPlane, nearPlaneNormal, viewedTriangle, clipped[0], clipped[1]);

    for (int n = 0; n < nClippedTriangles; n++) {
      Triangle projectedTriangle = clipped[n].getProjectedTriangle(projection);

      Vec3 vecPoint = viewedTriangle.vertices[0].normalize();

      // std::cout << "Normal:\n";
      // viewedTriangle.normal.display();

      float dotProduct = Math::dot(vecPoint, viewedTriangle.normal.normalize());
      if (dotProduct < 0) {
        uint32_t shade = 159 * std::min(1.0f, std::max(0.0f, -dotProduct)) + 96;
        shade = 0xFF000000 | (shade << 16) | (shade << 8) | (shade);

        for (int p = 0; p < 4; ++p) {
          Triangle rasterClipped[2];
          int nTrisToRaster = 0;
          switch (p) {
          case 0:
            nTrisToRaster = renderer.triangleClipAtPlane(
                top, topNormal, projectedTriangle, rasterClipped[0],
                rasterClipped[1]);
            break;
          case 1:
            nTrisToRaster = renderer.triangleClipAtPlane(
                bottom, bottomNormal, projectedTriangle, rasterClipped[0],
                rasterClipped[1]);
            break;
          case 2:
            nTrisToRaster = renderer.triangleClipAtPlane(
                left, leftNormal, projectedTriangle, rasterClipped[0],
                rasterClipped[1]);
            break;
          case 3:
            nTrisToRaster = renderer.triangleClipAtPlane(
                right, rightNormal, projectedTriangle, rasterClipped[0],
                rasterClipped[1]);
            break;
          }
          for (int w = 0; w < nTrisToRaster; ++w)
            toRender.push_back(rasterClipped[w]);
        }

        for (Triangle &clippedTriangle : toRender) {
          renderer.fillTriangle(clippedTriangle, shade);
        }
        toRender.clear();
      }
    }
  }

  transform = identityMatrix();
}
