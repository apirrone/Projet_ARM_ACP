#ifndef VOXEl_HPP
#define VOXEl_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>

class Voxel{

public:
  static enum Face {TOP = 0, BOTTOM = 1, FRONT = 2, REAR = 3, LEFT = 4, RIGHT = 5};
  Voxel(double x, double y, double z, double val);
  initVBA();
  void paint();
  
private:
  static VEF* _vef = NULL;
  static int _faceIndices[6][2];
  
  double _x, _y, _z, _value;
  unsigned int _vertexBufferId;
  bool _showFace[6], _changed;  
  };

#endif // VOXEl_HPP
