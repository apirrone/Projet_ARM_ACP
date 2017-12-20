#ifndef VEF_HPP
#define VEF_HPP

#include <vector>
#include <sstream>
#include <QtOpenGL>
#include <surface_mesh/surface_mesh.h>
#include "PolyhedronBuilder.hpp"
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Polyhedron_3.h>
#include "ext/eigen3/Eigen/Eigen"

typedef CGAL::Simple_cartesian<double> Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Polyhedron::HalfedgeDS HalfedgeDS;

// Base class for object composed of vertices, edges and faces
class VEF {

public:

  struct Vertex {

    Eigen::Vector3f position;
    Eigen::Vector3f normal;
    Eigen::Vector4f color;
    bool normalSet;

    Vertex() {
      position[0] = 0.;
      position[1] = 0.;
      position[2] = 0.;
      color[0] = 0.8;
      color[1] = 0.8;
      color[2] = 0.8;
      color[3] = 0.3;
      normalSet = false;

    }
    Vertex(float x, float y, float z) {
      position[0] = x;
      position[1] = y;
      position[2] = z;
      color[0] = 0.8;
      color[1] = 0.8;
      color[2] = 0.8;
      color[3] = 0.3;
      normalSet = false;
    }

    Vertex(float x, float y, float z, float r, float g, float b, float a) {
      position[0] = x;
      position[1] = y;
      position[2] = z;
      color[0] = r;
      color[1] = g;
      color[2] = b;
      color[3] = a;
      normalSet = false;
    }

    Vertex(Eigen::Vector3f pos, Eigen::Vector3f n) {
      position = pos;
      normal = n;
    }

    std::string toString() {
      std::stringstream ss;
      ss << "Vertex : position (" << position[0]  << "," << position[1] << "," << position[2] << ")" <<std::endl
	 << "\tnormal (" << normal[0]  << "," << normal[1] << "," << normal[2] << ")" << std::endl
	 << "\tcolor (" << color[0]  << "," << color[1] << "," << color[2] << "," << color[3] << ")" << std::endl;
      return ss.str();
    }
  };

  VEF();
  ~VEF();
  void loadFromObj(std::string filePath);
  void exportToObj(std::string exportFilePath);
  void HalfedgeToVEF();

  // getters & setters
  std::vector<Vertex>* getVertices();
  std::vector<unsigned int>* getEdges();
  std::vector<unsigned int>* getFaces();

  int addVertex(const Vertex& v);
  int addVertex(float x, float y, float z);
  int addEdge(int p1, int p2);
  int addFace(int e1, int e2, int e3);

  virtual void draw(QOpenGLShaderProgram* shader);

  void translate(QVector3D t);

  virtual QMatrix4x4 worldMatrix();

  void loadSurfaceMesh();
  void loadHalfEdges(std::string filePath);
  void halfedgeToObj(std::string exportFilePath);

  void fillHoleSimple();
  void fillHoleCenter();
  void fillHoleEarClipping();

  bool isEar(Polyhedron::Halfedge_handle he, const std::vector<Polyhedron::Halfedge_handle>& reflexVerts);
  bool isConvex(Polyhedron::Halfedge_handle he);

protected:
  std::vector<Vertex> _vertices;
  std::vector<unsigned int> _edges;
  std::vector<unsigned int> _faces;

  void initVAO();

  bool _initialized;//true if VAO has been initialized
  QOpenGLVertexArrayObject _vertexArray;
  QOpenGLBuffer* _vertexBuffer;
  QOpenGLBuffer* _indexBuffer;

  bool _updateWorldMat;
  QMatrix4x4 _worldMat;
  QVector3D _position;

  surface_mesh::Surface_mesh _surfaceMesh;
  Polyhedron _polyhedron;
};

#endif // VEF_HPP
