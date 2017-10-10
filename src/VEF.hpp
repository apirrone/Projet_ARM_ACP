#ifndef VEF_HPP
#define VEF_HPP

#include <vector>
#include <sstream>
#include <QtOpenGL>

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

    std::string toString() {
      std::stringstream ss;
      ss << "Vertex : position (" << position[0]  << "," << position[1] << "," << position[2] << ")" <<std::endl
	 << "\tnormal (" << normal[0]  << "," << normal[1] << "," << normal[2] << ")" << std::endl
	 << "\tcolor (" << color[0]  << "," << color[1] << "," << color[2] << "," << color[4] << ")" << std::endl;
      return ss.str();
    }
  };

  void loadFromObj(char* filePath);
  void exportToObj(char* exportFilePath);
  
  // getters & setters
  std::vector<Vertex>* getVertices();
  std::vector<unsigned int>* getEdges();
  std::vector<unsigned int>* getFaces();

  int addVertex(const Vertex& v);
  int addVertex(double x, double y, double z);
  int addEdge(int p1, int p2);
  int addFace(int e1, int e2, int e3);
  
  void draw(QOpenGLShaderProgram* shader);

  unsigned int getW();
  unsigned int getH();
  unsigned int getD();

protected:
  std::vector<Vertex> _vertices;
  std::vector<unsigned int> _edges;
  std::vector<unsigned int> _faces;
  
  void initVAO();
  
  bool _initialized;//true if VAO has been initialized
  QOpenGLVertexArrayObject _vertexArray;
  QOpenGLBuffer* _vertexBuffer;
  QOpenGLBuffer* _indexBuffer; 

  unsigned int _w, _h, _d, _minValue, _maxValue, _displayMinValue, _displayMaxValue;
};

#endif // VEF_HPP
