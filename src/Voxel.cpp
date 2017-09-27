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

  int e1 = this->addEdge(p1, p2);
  int e2 = this->addEdge(p2, p3);
  int e3 = this->addEdge(p3, p4);
  int e4 = this->addEdge(p4, p1);
  int e5 = this->addEdge(p5, p6);
  int e6 = this->addEdge(p6, p7);
  int e7 = this->addEdge(p7, p8);
  int e8 = this->addEdge(p5, p8);
  int e9 = this->addEdge(p1, p5);
  int e10 = this->addEdge(p2, p6);
  int e11 = this->addEdge(p3, p7);
  int e12 = this->addEdge(p4, p8);
  int e13 = this->addEdge(p1, p3);
  int e14 = this->addEdge(p1, p8);
  int e15 = this->addEdge(p2, p5);
  int e16 = this->addEdge(p3, p6);
  int e17 = this->addEdge(p6, p8);
  int e18 = this->addEdge(p4, p7);

  int f1 = this->addFace(e3, e4, e13);
  int f2 = this->addFace(e1, e2, e13);
  int f3 = this->addFace(e4, e12, e14);
  int f4 = this->addFace(e8, e9, e14);
  int f5 = this->addFace(e1, e9, e15);
  int f6 = this->addFace(e5, e10, e15);
  int f7 = this->addFace(e2, e10, e16);
  int f8 = this->addFace(e6, e11, e16);
  int f9 = this->addFace(e5, e8, e17);
  int f10 = this->addFace(e6, e17, e7);
  int f11 = this->addFace(e7, e12, e18);
  int f12 = this->addFace(e3, e11, e17);
}
