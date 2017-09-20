#include "Voxel.hpp"

Voxel::Voxel(double x, double y, double z, double val)
  : _x(x), _y(y), _z(z), _value(val) {
  int p1 = this->addVertex(_x-0.5, _y+0.5, _z+0.5);
  int p2 = this->addVertex(_x+0.5, _y+0.5, _z+0.5);
  int p3 = this->addVertex(_x+0.5, _y+0.5, _z-0.5);
  int p4 = this->addVertex(_x-0.5, _y+0.5, _z-0.5);
  int p5 = this->addVertex(_x-0.5, _y-0.5, _z+0.5);
  int p6 = this->addVertex(_x+0.5, _y-0.5, _z+0.5);
  int p7 = this->addVertex(_x+0.5, _y-0.5, _z-0.5);
  int p8 = this->addVertex(_x-0.5, _y-0.5, _z-0.5);

  int e1 = this->addEdge(p1,p2);
  int e2 = this->addEdge(p2,p3);
  int e3 = this->addEdge(p3,p4);
  int e4 = this->addEdge(p4,p1);
  int e5 = this->addEdge(p5,p6);
  int e6 = this->addEdge(p6,p7);
  int e7 = this->addEdge(p7,p8);
  int e8 = this->addEdge(p8,p5);
  int e9 = this->addEdge(p1,p5);
  int e10 = this->addEdge(p2,p6);
  int e11 = this->addEdge(p3,p7);
  int e12 = this->addEdge(p4,p8);

  //  int f1 = this->addface(
}


