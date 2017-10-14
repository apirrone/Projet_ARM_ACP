#include <QOpenGLShaderProgram>
#include <iostream>
#include <QOpenGLFunctions>

#include "VoxelGrid.hpp"

VoxelGrid::VoxelGrid(unsigned int h, unsigned int w, unsigned int d, const unsigned char* data)
  : _w(w), _h(h), _d(d) {

  _position = QVector3D(-1.*_w/2, 1.*_h/2, 1.*_d/2);
  std::cout << "h,w,d" << _h << " " << _w << " " << _d << '\n';

  unsigned int size = h*w*d;
  //créer tableau de voxels avec h w d
  _voxels = new Voxel[size];
  unsigned int maxVal, minVal;
  if(size > 0)
    maxVal = minVal = data[0];
  for(int i=0; i<h*w*d; ++i) {
    _voxels[i].value = data[i];
    if(data[i] > maxVal)
      maxVal = data[i];
    if(data[i] < minVal)
      minVal = data[i];
  }
  float r1 = 99., g1 = 0.8, b1 = 0., a1 = 0.6, r2 = 0., g2 = 0., b2 = 99., a2 = 0.1;

  for(int i=0; i<h; ++i)
    for(int j=0; j<w; ++j)
      for(int k=0; k<d; ++k) {
        //std::cout << "/* message */" << '\n';
	Voxel& current = _voxels[i*_w*_d + j*_d + k];
	double currentValue = _voxels[i*_w*_d + j*_d + k].value;
	if(currentValue == 0)
	  continue;
	//std::cout << "VOXELGRID : current value = " << currentValue << '\n';
	float r, g, b, alpha;
	//r = r1 + ((currentValue-minVal)/(maxVal-minVal)) * (r2-r1);
	//g = g1 + ((currentValue-minVal)/(maxVal-minVal)) * (g2-g1);
	//b = b1 + ((currentValue-minVal)/(maxVal-minVal)) * (b2-b1);
	//alpha = a1 + ((currentValue-minVal)/(maxVal-minVal)) * (a2-a1);
	if(currentValue == 0)
	  alpha = 0.;
	else
	  alpha = 0.1;
    r = g = b = 0.8;
	// std::cout << "test" << std::endl;
	VEF::Vertex v;
	//we create all the vertices

	//TFL
	v = VEF::Vertex(j-0.5, -i+0.5, -k+0.5, r, g, b, alpha);
	current.vertices[Voxel::Corner::TFL] = this->addVertex(v);
	//TFR
	v = VEF::Vertex(j+0.5, -i+0.5, -k+0.5, r, g, b, alpha);
	current.vertices[Voxel::Corner::TFR] = this->addVertex(v);
	//TRL
	v = VEF::Vertex(j-0.5, -i+0.5, -k-0.5, r, g, b, alpha);
	current.vertices[Voxel::Corner::TRL] = this->addVertex(v);
	//TRR
	v = VEF::Vertex(j+0.5, -i+0.5, -k-0.5, r, g, b, alpha);
	current.vertices[Voxel::Corner::TRR] = this->addVertex(v);
	//BFL
	v = VEF::Vertex(j-0.5, -i-0.5, -k+0.5, r, g, b, alpha);
	current.vertices[Voxel::Corner::BFL] = this->addVertex(v);
	//BFR
	v = VEF::Vertex(j+0.5, -i-0.5, -k+0.5, r, g, b, alpha);
	current.vertices[Voxel::Corner::BFR] = this->addVertex(v);
	//BRL
	v = VEF::Vertex(j-0.5, -i-0.5, -k-0.5, r, g, b, alpha);
	current.vertices[Voxel::Corner::BRL] = this->addVertex(v);
	//BRR
	v = VEF::Vertex(j+0.5, -i-0.5, -k-0.5, r, g, b, alpha);
	current.vertices[Voxel::Corner::BRR] = this->addVertex(v);
	//retrieve neighborhood
	Voxel * top, * bot, * left, * right, * front, * rear;
	top = getTopVoxel(i,j,k);
	bot = getBottomVoxel(i,j,k);
	left = getLeftVoxel(i,j,k);
	right = getRightVoxel(i,j,k);
	front = getFrontVoxel(i,j,k);
	rear = getRearVoxel(i,j,k);

	//check left
	if(left == NULL || left->value != current.value) {
	  this->addFace(current.vertices[Voxel::Corner::TFL],
			current.vertices[Voxel::Corner::TRL],
			current.vertices[Voxel::Corner::BRL]);
	  this->addFace(current.vertices[Voxel::Corner::TFL],
			current.vertices[Voxel::Corner::BRL],
			current.vertices[Voxel::Corner::BFL]);
	}

	//check right
	if(right == NULL || right->value != current.value) {
	  this->addFace(current.vertices[Voxel::Corner::TRR],
			current.vertices[Voxel::Corner::TFR],
			current.vertices[Voxel::Corner::BFR]);
	  this->addFace(current.vertices[Voxel::Corner::TRR],
		       current.vertices[Voxel::Corner::BFR],
		       current.vertices[Voxel::Corner::BRR]);
	}
	//check top
	if(top == NULL || top->value != current.value) {
	  this->addFace(current.vertices[Voxel::Corner::TRR],
			current.vertices[Voxel::Corner::TRL],
			current.vertices[Voxel::Corner::TFL]);
	  this->addFace(current.vertices[Voxel::Corner::TRR],
		       current.vertices[Voxel::Corner::TFL],
		       current.vertices[Voxel::Corner::TFR]);
	}
	//check bot
	if(bot == NULL || bot->value != current.value) {
	  this->addFace(current.vertices[Voxel::Corner::BFR],
			current.vertices[Voxel::Corner::BFL],
			current.vertices[Voxel::Corner::BRL]);
	  this->addFace(current.vertices[Voxel::Corner::BFR],
			current.vertices[Voxel::Corner::BRL],
			current.vertices[Voxel::Corner::BRR]);
	}
	//check front
	if(front == NULL || front->value != current.value) {
	  this->addFace(current.vertices[Voxel::Corner::TFR],
			current.vertices[Voxel::Corner::TFL],
			current.vertices[Voxel::Corner::BFL]);
	  this->addFace(current.vertices[Voxel::Corner::TFR],
			current.vertices[Voxel::Corner::BFL],
			current.vertices[Voxel::Corner::BFR]);
	}

	//check rear
	if(rear == NULL || rear->value != current.value) {
	  this->addFace(current.vertices[Voxel::Corner::TRL],
			current.vertices[Voxel::Corner::TRR],
			current.vertices[Voxel::Corner::BRR]);
	  this->addFace(current.vertices[Voxel::Corner::TRL],
			current.vertices[Voxel::Corner::BRR],
			current.vertices[Voxel::Corner::BRL]);
	}
      }

}

VoxelGrid::Voxel* VoxelGrid::getLeftVoxel(int i, int j, int k) {
  if(j > 0)
    return &_voxels[i*_w*_d + (j-1)*_d + k];
  else
    return NULL;
}

VoxelGrid::Voxel* VoxelGrid::getRightVoxel(int i, int j, int k) {
  if(j < _w-1)
    return &_voxels[i*_w*_d + (j+1)*_d + k];
  else
    return NULL;
}

VoxelGrid::Voxel* VoxelGrid::getTopVoxel(int i, int j, int k) {
  if(i > 0)
    return &_voxels[(i-1)*_w*_d + j*_d + k];
  else
    return NULL;
}

VoxelGrid::Voxel* VoxelGrid::getBottomVoxel(int i, int j, int k) {
  if(i < _h-1)
    return &_voxels[(i+1)*_w*_d + j*_d + k];
  else
    return NULL;
}

VoxelGrid::Voxel* VoxelGrid::getFrontVoxel(int i, int j, int k) {
  if(k > 0)
    return &_voxels[i*_w*_d + j*_d + (k-1)];
  else
    return NULL;
}

VoxelGrid::Voxel* VoxelGrid::getRearVoxel(int i, int j, int k) {
  if(k < _d-1)
    return &_voxels[i*_w*_d + j*_d + (k+1)];
  else
    return NULL;
}

VoxelGrid::~VoxelGrid() {
  //free _voxels


  //_vertexBufferId.destroy();
  //_vertexArrayId.destroy();
}

void VoxelGrid::initVAO() {
  _vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  _vertexBuffer->create();
  _vertexBuffer->bind();
  _vertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
  _vertexBuffer->allocate(&(_vertices[0]), sizeof(VEF::Vertex)*_vertices.size());

  _indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  _indexBuffer->create();
  _indexBuffer->bind();
  _indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
  _indexBuffer->allocate(&(_faces[0]), sizeof(unsigned int)*_faces.size());

  _vertexArray.create();

  _initialized = true;

}

unsigned int VoxelGrid::getW(){
  return _w;
}

unsigned int VoxelGrid::getH(){
  return _h;
}

unsigned int VoxelGrid::getD(){
  return _d;
}
