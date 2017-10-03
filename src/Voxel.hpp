#ifndef VOXEl_HPP
#define VOXEl_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>

class Voxel{

public:
  Voxel(double x, double y, double z, double val);
  initVBA();
  void paint();
  
private:
  static VEF* _vef = NULL;
  double _x, _y, _z, _value;
  unsigned int _vertexBufferId;
  static const double[] _voxelVertices = {-0.5, 0.5, 0.5,
					  0.5, 0.5, 0.5,
					  O.5, 0.5, -0.5,
					  -0.5, 0.5, -0.5,
					  -0.5, -0.5, 0.5,
					  0.5, -0.5, 0.5,
					  0.5, -0.5, -0.5,
					  -0.5, -0.5, -0.5};
  static const int[] _voxelFaces = {2, 3, 0, 0, 1, 3,
				    0, 3, 8
  };

#endif // VOXEl_HPP
