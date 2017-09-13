#include <vector>
#include "VEF.hpp"

// getters
std::vector<VEF::Vertex*>& VEF::getVertices() {
  return _vertices;
}

std::vector<VEF::Edge*>& VEF::getEdges() {
  return _edges;
}

std::vector<VEF::Face*>& VEF::getFaces() {
  return _faces;
}

// setters
void VEF::addVertex(VEF::Vertex& vert) {
  _vertices.push_back(&vert);
}

void VEF::addEdge(VEF::Edge& edge) {
  _edges.push_back(&edge);
}

void VEF::addFace(VEF::Face& face) {
  _faces.push_back(&face);
}
