#include "VoxelGrid.hpp"

VoxelGrid::VoxelGrid(unsigned int h, unsigned int w, unsigned int d, unsigned char* data)
  : _w(w), _h(h), _d(d) {
  //créer tableau de voxels avec h w d
  _voxels = new Voxel[h*w*d];
  for(int i=0; i<h*w*d; ++i) {
    _voxels[i]->value = data[i];
  }

  for(int i=0; i<h; ++i)
    for(int j=0; j<w; ++j)
      for(int k=0; k<d; ++k) {
	Voxel * current = _voxels[i*_w*_d + j*_d + k];
	
	//retrieve neighborhood
	Voxel * top, bot, left, right, front, rear;
	top = getTopVoxel(i,j,k);
	bot = getBottomVoxel(i,j,k);
	left = getLeftVoxel(i,j,k);
	right = getRightVoxel(i,j,k);
	front = getFrontVoxel(i,j,k);
	rear = getRearVoxel(i,j,k);
	
	//check left
	
	//check right

	//check top

	//check bot

	//check front

	//check rear
	
      }
}

Voxel* VoxelGrid::getLeftVoxel(int i, int j, int k) {
  if(j > 0)
    return _voxels[i*_w*_d + (j-1)*_d + k];
  else
    return std::nullptr;
}

Voxel* VoxelGrid::getRightVoxel(int i, int j, int k) {
  if(j < _w-1)
    return _voxels[i*_w*_d + (j+1)*_d + k];
  else
    return std::nullptr;
}

Voxel* VoxelGrid::getTopVoxel(int i, int j, int k) {
  if(i > 0)
    return _voxels[(i-1)*_w*_d + j*_d + k];
  else
    return std::nullptr;
}

Voxel* VoxelGrid::getBottomVoxel(int i, int j, int k) {
  if(i < _h-1)
    return _voxels[(i+1)*_w*_d + j*_d + k];
  else
    return std::nullptr;
}

Voxel* VoxelGrid::getFrontVoxel(int i, int j, int k) {
  if(k > 0)
    return _voxels[i*_w*_d + j*_d + (k-1)];
  else
    return std::nullptr;
}

Voxel* VoxelGrid::getRearVoxel(int i, int j, int k) {
  if(k < _d-1)
    return _voxels[i*_w*_d + j*_d + (k+1)];
  else
    return std::nullptr;
}

~VoxelGrid::VoxelGrid() {
  //free _voxels
  //détruire les objets openGL
}

void VoxelGrid::draw();

void VoxelGrid::initVAO();
void VoxelGrid::initVEF();
