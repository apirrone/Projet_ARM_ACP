#ifndef VOXEl_HPP
#define VOXEl_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>

#include "VEF.hpp"

class Voxel : public VEF {

public:
  Voxel(double x, double y, double z, double val);
  void paint();
  
private:
  double _x, _y, _z, _value;
};

#endif // VOXEl_HPP
