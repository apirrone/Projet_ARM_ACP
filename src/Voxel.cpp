#include "Voxel.hpp"
#include <iostream>
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

void Voxel::paint(){

  int val = _value/255;
  
  // glColor3f(val,val,val);  
  glColor3f(1, 0, 0);  

  for(int i = 0 ; i < _faces.size() ; i+=3){

    int e1 = _faces.at(i);
    int e2 = _faces.at(i+1);
    int e3 = _faces.at(i+2);

    int v1 = _edges.at(e1);
    int v2 = _edges.at(e1+1);

    int v3 = _edges.at(e2);
    int v4 = _edges.at(e2+1);

    int v5 = _edges.at(e3);
    int v6 = _edges.at(e3+1);
    
    double v1_x = _vertices.at(v1);
    double v1_y = _vertices.at(v1+1);
    double v1_z = _vertices.at(v1+2);

    double v2_x = _vertices.at(v2);
    double v2_y = _vertices.at(v2+1);
    double v2_z = _vertices.at(v2+2);

    double v3_x = _vertices.at(v3);
    double v3_y = _vertices.at(v3+1);
    double v3_z = _vertices.at(v3+2);

    double v4_x = _vertices.at(v4);
    double v4_y = _vertices.at(v4+1);
    double v4_z = _vertices.at(v4+2);
    
    double v5_x = _vertices.at(v5);
    double v5_y = _vertices.at(v5+1);
    double v5_z = _vertices.at(v5+2); 
    
    double v6_x = _vertices.at(v6);
    double v6_y = _vertices.at(v6+1);
    double v6_z = _vertices.at(v6+2);
    // std::cout << "coucou6" << std::endl;
 
    glVertex3f(v1_x, v1_y, v1_z);
    glVertex3f(v2_x, v2_y, v2_z);
    glVertex3f(v3_x, v3_y, v3_z);

    // glVertex3f(v4_x, v4_y, v4_z);
    // glVertex3f(v5_x, v5_y, v5_z);
    // glVertex3f(v6_x, v6_y, v6_z);
  } 
  
}
