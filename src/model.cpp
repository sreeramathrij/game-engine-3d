#include "model.h"
#include "transforms.h"


Model::Model(const Mesh& mesh, Renderer& renderer,const Vec3& cameraPos, const Mat4& projection) : mesh(mesh), renderer(renderer), cameraPos(cameraPos), projection(projection), transform(identityMatrix()){}

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
    
    Triangle projectedTriangle = transformedTriangle.getProjectedTriangle(projection); 

    Vec3 vecPoint = (transformedTriangle.vertices[0] - cameraPos).normalize();
    //std::cout << "Projected:\n";
    //projectedTriangle.vertices[0].display();
    //projectedTriangle.vertices[1].display();
    //projectedTriangle.vertices[2].display();
  

    //std::cout << "Normal:\n";
    //transformedTriangle.normal.display();

    float dotProduct = Math::dot(vecPoint, transformedTriangle.normal.normalize());
    if(dotProduct < 0) {
      uint32_t shade = 159 * std::min(1.0f, std::max(0.0f, -dotProduct)) + 96;
      shade = 0xFF000000 | (shade << 16) | (shade << 8) | (shade);
      //projectedTriangle.vertices[0].display();
      //projectedTriangle.vertices[1].display();
      //projectedTriangle.vertices[2].display();
      //std::cout << "shade: " << shade;
      renderer.fillTriangle(projectedTriangle, shade);
    }
  }
  
  transform = identityMatrix();
}
