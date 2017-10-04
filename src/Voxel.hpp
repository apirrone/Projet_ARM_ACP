#ifndef VOXEl_HPP
#define VOXEl_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>

class Voxel : public VEF{

public:
  static enum Face {TOP = 0, BOTTOM = 1, FRONT = 2, REAR = 3, LEFT = 4, RIGHT = 5};
  Voxel(double x, double y, double z, double val);
  void paint();
  
private:
  int _faceIndices[6][2];
  
  double _x, _y, _z, _value;
  unsigned int _vertexBufferId;
  unsigned int _vertexArrayId;
  bool _showFace[6], _changed;
  bool _initialized;
  
  
  };

#endif // VOXEl_HPP
