#ifndef VEF_HPP
#define VEF_HPP

// Base class for object composed of vertices, edges and faces
class VEF {

public:

  // TODO arrays ?
  struct Vertex {
    double x;
    double y;
    double z;

    Vertex(double x, double y, double z)
    :x(x),y(y),z(z) {}
  };

  struct Edge {
    Vertex& v1;
    Vertex& v2;

    Edge(Vertex& v1, Vertex& v2)
    :v1(v1),v2(v2) {}
  };

  struct Face {
    Edge& e1;
    Edge& e2;
    Edge& e3;

    Face(Edge& e1, Edge& e2, Edge& e3)
    :e1(e1),e2(e2),e3(e3) {}
  };

  // getters & setters
  std::vector<Vertex*>& getVertices();
  std::vector<Edge*>& getEdges();
  std::vector<Face*>& getFaces();

  void addVertex(Vertex& vertex);
  void addEdge(Edge& edge);
  void addFace(Face& face);

private:
  std::vector<Vertex*> _vertices;
  std::vector<Edge*> _edges;
  std::vector<Face*> _faces;

};

#endif // VEF_HPP
