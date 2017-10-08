#ifndef VEF_HPP
#define VEF_HPP

#include <vector>


// Base class for object composed of vertices, edges and faces
class VEF {

public:

  
  struct Vertex {
    float position[3];
    float normal[3];
    float color[4];
    
    Vertex() {
      position[0] = 0.;
      position[1] = 0.;
      position[2] = 0.;
      color[0] = 0.8;
      color[1] = 0.8;
      color[2] = 0.8;
      color[3] = 0.3;
    }
    Vertex(double x, double y, double z) {
      position[0] = x;
      position[1] = y;
      position[2] = z;
      color[0] = 0.8;
      color[1] = 0.8;
      color[2] = 0.8;
      color[3] = 0.3;
    }

    Vertex(double x, double y, double z, float r, float g, float b, float a) {
      position[0] = x;
      position[1] = y;
      position[2] = z;
      color[0] = r;
      color[1] = g;
      color[2] = b;
      color[3] = a;
    }    
  };
  
  // getters & setters
  std::vector<Vertex>* getVertices();
  std::vector<unsigned int>* getEdges();
  std::vector<unsigned int>* getFaces();

  int addVertex(const Vertex& v);
  int addVertex(double x, double y, double z);
  int addEdge(int p1, int p2);
  int addFace(int e1, int e2, int e3);

protected:
  std::vector<Vertex> _vertices;
  std::vector<unsigned int> _edges;
  std::vector<unsigned int> _faces;
};

#endif // VEF_HPP
