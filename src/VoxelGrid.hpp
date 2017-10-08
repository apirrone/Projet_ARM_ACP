#ifndef VOXEL_GRID_HPP
#define VOXEL_GRID_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include "VEF.hpp"

class VoxelGrid : public VEF {

  
public :
  VoxelGrid(unsigned int h, unsigned int w, unsigned int d, const unsigned char* data);
  ~VoxelGrid();
  
  void draw(QOpenGLShaderProgram* shader);
    
private :

  struct Voxel {
    //XYZ
    //X : T = TOP, B = BOTTOM
    //Y : F = FRONT, R = REAR
    //Z : L = LEFT, R = RIGHT
    enum Corner{TFL = 0, TFR = 1, TRL = 2, TRR = 3, BFL = 4, BFR = 5, BRL = 6, BRR = 7};
    int vertices[8];
    double value;

    Voxel() : value(0) {
      for(int i=0; i<8; ++i){
	vertices[i] = -1;
      }
    }
  };

  Voxel* getTopVoxel(int, int, int);
  Voxel* getBottomVoxel(int, int, int);
  Voxel* getLeftVoxel(int, int, int);
  Voxel* getRightVoxel(int, int, int);
  Voxel* getFrontVoxel(int, int, int);
  Voxel* getRearVoxel(int, int, int);
  
  bool _initialized;//true if VAO has been initialized
  //QOpenGLVertexArrayObject _vertexArrayId;
  //QOpenGLBuffer* _vertexBufferId;
  //QOpenGLBuffer* _indexBufferId;
  unsigned int _vertexArrayId;
  unsigned int _vertexBufferId;
  unsigned int _faceBufferId;

  Voxel* _voxels;

  unsigned int _w, _h, _d;
  
  void initVAO();
  void fillVBO();
};


#endif // VOXEL_GRID_HPP
