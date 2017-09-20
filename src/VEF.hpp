#ifndef VEF_HPP
#define VEF_HPP

#include <vector>


// Base class for object composed of vertices, edges and faces
class VEF {

public:
  // getters & setters
  std::vector<double>* getVertices();
  std::vector<int>* getEdges();
  std::vector<int>* getFaces();

  int addVertex(double x, double y, double z);
  int addEdge(int p1, int p2);
  int addFace(int e1, int e2, int e3, int e4);

private:
  std::vector<double> _vertices;
  std::vector<int> _edges;
  std::vector<int> _faces;
};

#endif // VEF_HPP
