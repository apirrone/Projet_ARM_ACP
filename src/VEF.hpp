#ifndef VEF_HPP
#define VEF_HPP

#include <vector>


// Base class for object composed of vertices, edges and faces
class VEF {

public:
  
  struct Vertex {
    Vertex() {
      position[0] = 0.;
      position[1] = 0.;
      position[2] = 0.;
      color[0] = 0.8;
      color[1] = 0.8;
      color[2] = 0.8;
      color[3] = 1.0;
    }
    Vertex(double x, double y, double z) {
      position[0] = x;
      position[1] = y;
      position[2] = z;
      color[0] = 0.8;
      color[1] = 0.8;
      color[2] = 0.8;
      color[3] = 1.0;
    }
    
    double position[3];
    double normal[3];
    double color[4];
  };
  
  // getters & setters
  std::vector<Vertex>* getVertices();
  std::vector<int>* getEdges();
  std::vector<int>* getFaces();

  int addVertex(const Vertex& v);
  int addVertex(double x, double y, double z);
  int addEdge(int p1, int p2);
  int addFace(int e1, int e2, int e3);

protected:
  std::vector<Vertex> _vertices;
  std::vector<int> _edges;
  std::vector<int> _faces;
};

#endif // VEF_HPP
