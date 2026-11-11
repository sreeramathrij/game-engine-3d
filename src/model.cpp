#include "model.h"
#include "transforms.h"


Model::Model(const Mesh& mesh, Renderer& renderer,const Vec3& cameraPos, const Mat4& projection, Mat4& view) : mesh(mesh), renderer(renderer), cameraPos(cameraPos), projection(projection), view(view), transform(identityMatrix()){}

// Rotates the model by multiplying the current transformation matrix with a rotation matrix
void Model::rotate(const Vec3& rotation){
 transform = transform * rotationMatrix(rotation); 
}

// Translates the model by multiplying the current transformation matrix with a translation matrix
void Model::translate(const Vec3& translation){
  transform = transform * translationMatrix(translation); 
}

// Renders the model by transforming then projecting each triangle to screen space
void Model::render() {
  Vec3 top(0.0f, 0.0f, 0.0f), topNormal(0.0f, 1.0f, 0.0f);
  Vec3 bottom(0.0f, (float)renderer.height - 1 , 0.0f), bottomNormal(0.0f, -1.0f, 0.0f);
  Vec3 left(0.0f, 0.0f, 0.0f), leftNormal(1.0f, 0.0f, 0.0f);
  Vec3 right(0.0f, (float)renderer.width - 1, 0.0f), rightNormal(-1.0f, 0.0f, 0.0f);

  for(auto triangle: mesh.triangles) {
    //std::cout << "Original Triangle:\n";
    //triangle.vertices[0].display();
    //triangle.vertices[1].display();
    //triangle.vertices[2].display();

    Triangle transformedTriangle(triangle.getTransformedTriangle(transform)); 
    //std::cout << "Transformed:\n";
    //transformedTriangle.vertices[0].display();
    //transformedTriangle.vertices[1].display();
    //transformedTriangle.vertices[2].display();

    Triangle viewedTriangle(transformedTriangle.getViewedTriangle(view));

    int nClippedTriangles = 0;
    Triangle clipped[2];

    Vec3 nearPlane(0.0f, 0.0f, 0.1f);
    Vec3 nearPlaneNormal(0.0f, 0.0f, 1.0f);
    nClippedTriangles = renderer.triangleClipAtPlane(nearPlane, nearPlaneNormal, viewedTriangle, clipped[0], clipped[1]);

    
    for(int n = 0; n < nClippedTriangles; n++) {
      Triangle projectedTriangle = clipped[n].getProjectedTriangle(projection); 

      Vec3 vecPoint = viewedTriangle.vertices[0].normalize();
      //std::cout << "Projected:\n";
      //projectedTriangle.vertices[0].display();
      //projectedTriangle.vertices[1].display();
      //projectedTriangle.vertices[2].display();
    

      //std::cout << "Normal:\n";
      //viewedTriangle.normal.display();

      float dotProduct = Math::dot(vecPoint, viewedTriangle.normal.normalize());
      if(dotProduct < 0) {
        uint32_t shade = 159 * std::min(1.0f, std::max(0.0f, -dotProduct)) + 96;
        shade = 0xFF000000 | (shade << 16) | (shade << 8) | (shade);
        //projectedTriangle.vertices[0].display();
        //projectedTriangle.vertices[1].display();
        //projectedTriangle.vertices[2].display();
        //std::cout << "shade: " << shade;
        
        for(int p=0; p<4; ++p){
          int nTrisToRaster = 0;
          switch(p) {
            case 0: nTrisToRaster = renderer.triangleClipAtPlane(top, topNormal, projectedTriangle, clipped[0], clipped[1]); break;
            case 1: nTrisToRaster = renderer.triangleClipAtPlane(bottom, bottomNormal, projectedTriangle, clipped[0], clipped[1]); break;
            case 2: nTrisToRaster = renderer.triangleClipAtPlane(left, leftNormal, projectedTriangle, clipped[0], clipped[1]); break;
            case 3: nTrisToRaster = renderer.triangleClipAtPlane(right, rightNormal, projectedTriangle, clipped[0], clipped[1]); break;
          }

          for(int w=0; w < nTrisToRaster; ++w)
            renderer.fillTriangle(clipped[w], shade);
        }
        // renderer.fillTriangle(projectedTriangle, shade);
      }
    }
  }
  
  transform = identityMatrix();
}
