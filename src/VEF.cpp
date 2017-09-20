#include <vector>
#include "VEF.hpp"

// getters
std::vector<double>* VEF::getVertices() {
  return &_vertices;
}

std::vector<int>* VEF::getEdges() {
  return &_edges;
}

std::vector<int>* VEF::getFaces() {
  return &_faces;
}

// setters
//add an element and returns its index in the VEF
int VEF::addVertex(double x, double y, double z) {
  int id = _vertices.size();
  _vertices.push_back(x);
  _vertices.push_back(y);
  _vertices.push_back(z);
  return id;
}

int VEF::addEdge(int p1, int p2) {
  int id = _edges.size();
  _edges.push_back(p1);
  _edges.push_back(p2);
  return id;
}

int VEF::addFace(int e1, int e2, int e3, int e4) {
  int id = _faces.size();
  _faces.push_back(e1);
  _faces.push_back(e2);
  _faces.push_back(e3);
  _faces.push_back(e4);
  return id;
}
