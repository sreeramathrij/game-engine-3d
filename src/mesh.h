#include "math.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace Math;

// Triangle class to represent the triangle in 3d space / screen space
class Triangle {
public:
  std::vector<Vec3> vertices;
  Vec3 normal, line1, line2;

public:
  Triangle() : vertices(3, Vec3(0.0f, 0.0f, 0.0f)){}

  Triangle(Vec3 v1, Vec3 v2, Vec3 v3) : vertices(3) {
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;

    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;

    line1 = v2 - v1;
    line2 = v3 - v1;
    normal = line1.cross(line2);
  }

  Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 normal) : vertices(3), normal(normal) {
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
  }
  
  Triangle(Triangle& triangle, Vec3 normal) : vertices(triangle.vertices), normal(normal) {}

  const Vec3& getNormal() const { return normal; }

  // Transforms the triangle by multiplying each vertex and the normal with the transformation matrix
  Triangle getTransformedTriangle(const Mat4& transform) {
    Triangle transformedTriangle;

    transformedTriangle.vertices[0] = Vec4(vertices[0], 1) * transform;
    transformedTriangle.vertices[1] = Vec4(vertices[1], 1) * transform;
    transformedTriangle.vertices[2] = Vec4(vertices[2], 1) * transform;

    transformedTriangle.normal = Vec4(normal, 0) * transform;

    return transformedTriangle;
  }
  
  // Projects the current triangle coords on to screen space by multiplying each vertex with the projection matrix
  Triangle getProjectedTriangle(const Mat4& projection) {
    Triangle projectedTriangle;

    Vec4 vertex = Vec4(vertices[0], 1.0f) * projection;
    if(vertex.w != 0.0f) 
      projectedTriangle.vertices[0] = vertex / vertex.w;

    vertex = Vec4(vertices[1], 1.0f) * projection;
    if(vertex.w != 0.0f) 
      projectedTriangle.vertices[1] = vertex / vertex.w;

    vertex = Vec4(vertices[2], 1.0f) * projection;
    if(vertex.w != 0.0f) 
      projectedTriangle.vertices[2] = vertex / vertex.w;

    return projectedTriangle;
  }
};

// Mesh class to represent the mesh of triangles loaded from the obj file
class Mesh {
private:
  std::string fileName;

public:
  std::vector<Triangle> triangles;

public:
  Mesh(const std::string &fileName) : fileName(fileName) {}

  bool loadObjectFromFile() {
    std::ifstream file(fileName);
    if (!file.is_open())
      return false;

    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;

    std::string line;
    while (std::getline(file, line)) {
      std::stringstream sStream;
      sStream << line;

      char junk;
      int trash;
      if (line[0] == 'v' && line[1] == 'n') {
        Vec3 vn;
        sStream >> junk >> junk >> vn.x >> vn.y >> vn.z;
        normals.push_back(vn);
      } else if (line[0] == 'v' && line[1] == 't') {
        continue;
      } else if (line[0] == 'v') {
        Vec3 v;
        sStream >> junk >> v.x >> v.y >> v.z;
        vertices.push_back(v);
        v.display();
      } else if (line[0] == 'f') {
        int f[3];
        int n;
        sStream >> junk >> f[0] >> junk >> trash >> junk >> n >> f[1] >> junk >>
            trash >> junk >> trash >> f[2] >> junk >> trash;
        triangles.push_back(Triangle(vertices[f[0] - 1], vertices[f[1] - 1],
                                     vertices[f[2] - 1], normals[n - 1]));
      }
    }
    return true;
  }
};

class Cube {
public:
  Triangle triangles[12];

public:
  Cube() {}

  void init() {
    Vec3 v1(0.0f, 0.0f, 0.0f);
    Vec3 v2(0.0f, 1.0f, 0.0f);
    Vec3 v3(1.0f, 1.0f, 0.0f);

    Vec3 v4(0.0f, 0.0f, 0.0f);
    Vec3 v5(1.0f, 1.0f, 0.0f);
    Vec3 v6(1.0f, 0.0f, 0.0f);

    Vec3 v7(1.0f, 0.0f, 0.0f);
    Vec3 v8(1.0f, 1.0f, 0.0f);
    Vec3 v9(1.0f, 1.0f, 1.0f);

    Vec3 v10(1.0f, 0.0f, 0.0f);
    Vec3 v11(1.0f, 1.0f, 1.0f);
    Vec3 v12(1.0f, 0.0f, 1.0f);

    Vec3 v13(1.0f, 0.0f, 1.0f);
    Vec3 v14(1.0f, 1.0f, 1.0f);
    Vec3 v15(0.0f, 1.0f, 1.0f);

    Vec3 v16(1.0f, 0.0f, 1.0f);
    Vec3 v17(0.0f, 1.0f, 1.0f);
    Vec3 v18(0.0f, 0.0f, 1.0f);

    Vec3 v19(0.0f, 0.0f, 1.0f);
    Vec3 v20(0.0f, 1.0f, 1.0f);
    Vec3 v21(0.0f, 1.0f, 0.0f);

    Vec3 v22(0.0f, 0.0f, 1.0f);
    Vec3 v23(0.0f, 1.0f, 0.0f);
    Vec3 v24(0.0f, 0.0f, 0.0f);

    Vec3 v25(0.0f, 1.0f, 0.0f);
    Vec3 v26(0.0f, 1.0f, 1.0f);
    Vec3 v27(1.0f, 1.0f, 1.0f);

    Vec3 v28(0.0f, 1.0f, 0.0f);
    Vec3 v29(1.0f, 1.0f, 1.0f);
    Vec3 v30(1.0f, 1.0f, 0.0f);

    Vec3 v31(1.0f, 0.0f, 0.0f);
    Vec3 v32(1.0f, 0.0f, 1.0f);
    Vec3 v33(0.0f, 0.0f, 1.0f);

    Vec3 v34(1.0f, 0.0f, 0.0f);
    Vec3 v35(0.0f, 0.0f, 1.0f);
    Vec3 v36(0.0f, 0.0f, 0.0f);

    triangles[0] = Triangle(v1, v2, v3);
    triangles[1] = Triangle(v4, v5, v6);

    triangles[2] = Triangle(v7, v8, v9);
    triangles[3] = Triangle(v10, v11, v12);

    triangles[4] = Triangle(v13, v14, v15);
    triangles[5] = Triangle(v16, v17, v18);

    triangles[6] = Triangle(v19, v20, v21);
    triangles[7] = Triangle(v22, v23, v24);

    triangles[8] = Triangle(v25, v26, v27);
    triangles[9] = Triangle(v28, v29, v30);

    triangles[10] = Triangle(v31, v32, v33);
    triangles[11] = Triangle(v34, v35, v36);
  };
};
