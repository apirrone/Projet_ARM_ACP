#ifndef VOXEl_GRID_HPP
#define VOXEl_GRID_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>

class VoxelGrid : public VEF {

  
public :
  VoxelGrid(unsigned int h, unsigned int w, unsigned int d, unsigned char* data);
  ~VoxelGrid();
  
  void draw();
    
private :

  struct Voxel {
    //XYZ
    //X : T = TOP, B = BOTTOM
    //Y : F = FRONT, R = REAR
    //Z : L = LEFT, R = RIGHT
    static enum Corner{TFL = 0, TFR = 1, TRL = 2, TRR = 3, BFL = 4, BFR = 5, BRL = 6, BRR = 7};
    int vertices[8];
    double value;

    Voxel() : value(0) {
      for(int i=0; i<8; ++i){
	vertices[i] = std::nullptr;
      }
    }
  };

  bool _initialized;//true if VAO has been initialized
  unsigned int _vertexArrayId;
  unsigned int _vertexBufferId;
  unsigned int _vertexColorId;  

  Voxel* _voxels;

  unsigned int _w, _h, _d;
  
  void initVAO();
  void fillVBO();
  void initVEF();

};


#endif // VOXEL_GRID_HPP
