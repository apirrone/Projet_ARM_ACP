#include <QOpenGLShaderProgram>
#include <iostream>
#include <QOpenGLFunctions>

#include "VoxelGrid.hpp"

VoxelGrid::VoxelGrid(unsigned int h, unsigned int w, unsigned int d, const unsigned char* data)
  : _w(w), _h(h), _d(d) {

  //créer tableau de voxels avec h w d
  _voxels = new Voxel[h*w*d];
  for(int i=0; i<h*w*d; ++i) {
    _voxels[i].value = data[i];
  }

  for(int i=0; i<h; ++i)
    for(int j=0; j<w; ++j)
      for(int k=0; k<d; ++k) {
	Voxel& current = _voxels[i*_w*_d + j*_d + k];
	double currentValue = _voxels[i*_w*_d + j*_d + k].value;
	// std::cout << "test" << std::endl;
	VEF::Vertex v;
	//we create all the vertices
	//TFL
	v = VEF::Vertex(i-0.5f, j+0.5f, k+0.5f, currentValue, currentValue, currentValue, 0.1);
	current.vertices[Voxel::Corner::TFL] = this->addVertex(v);
	//TFR
	v = VEF::Vertex(i+0.5f, j+0.5f, k+0.5f, currentValue, currentValue, currentValue, 0.1);
	current.vertices[Voxel::Corner::TFR] = this->addVertex(v);
	//TRL
	v = VEF::Vertex(i-0.5f, j+0.5f, k-0.5f, currentValue, currentValue, currentValue, 0.1);
	current.vertices[Voxel::Corner::TRL] = this->addVertex(v);
	//TRR
	v = VEF::Vertex(i+0.5f, j+0.5f, k-0.5f, currentValue, currentValue, currentValue, 0.1);
	current.vertices[Voxel::Corner::TRR] = this->addVertex(v);
	//BFL
	v = VEF::Vertex(i-0.5f, j-0.5f, k+0.5f, currentValue, currentValue, currentValue, 0.1);
	current.vertices[Voxel::Corner::BFL] = this->addVertex(v);
	//BFR
	v = VEF::Vertex(i+0.5f, j-0.5f, k+0.5f, currentValue, currentValue, currentValue, 0.1);
	current.vertices[Voxel::Corner::BFR] = this->addVertex(v);
	//BRL
	v = VEF::Vertex(i-0.5f, j-0.5f, k-0.5f, currentValue, currentValue, currentValue, 0.1);
	current.vertices[Voxel::Corner::BRL] = this->addVertex(v);
	//BRR
	v = VEF::Vertex(i+0.5f, j-0.5f, k-0.5f, currentValue, currentValue, currentValue, 0.1);
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
    return &_voxels[i*_w*_d + j*_d + (k+1)];
  else
    return NULL;
}

VoxelGrid::Voxel* VoxelGrid::getRearVoxel(int i, int j, int k) {
  if(k < _d-1)
    return &_voxels[i*_w*_d + j*_d + (k-1)];
  else
    return NULL;
}

VoxelGrid::~VoxelGrid() {
  //free _voxels


  //_vertexBufferId.destroy();
  //_vertexArrayId.destroy();
}

void VoxelGrid::draw(QOpenGLShaderProgram* shader){

  // std::cout << "VOXELGRID DRAW" << std::endl;
  if(!_initialized)
   initVAO();
  
  QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();  

  _vertexArray.bind();
  _indexBuffer->bind();
  
  int vertex_loc = shader->attributeLocation("vtx_position"); 
  if(vertex_loc>=0) {
    shader->setAttributeBuffer(vertex_loc, GL_FLOAT, offsetof(VEF::Vertex,position), 3, sizeof(VEF::Vertex));
    shader->enableAttributeArray(vertex_loc);
  }

  int color_loc = shader->attributeLocation("vtx_color");
  if(color_loc>=0) {
    shader->setAttributeBuffer(color_loc, GL_FLOAT, offsetof(VEF::Vertex,color), 4, sizeof(VEF::Vertex));
    shader->enableAttributeArray(color_loc);
  }  

  glDrawElements(GL_TRIANGLES, _faces.size(), GL_UNSIGNED_INT, 0);
  _indexBuffer->release();
  _vertexArray.release();  
}

void VoxelGrid::initVAO() {
  /*
  VEF::Vertex v1, v2, v3;
  v1.position[0] = -1;
  v1.position[1] = -1;
  v1.position[2] = -5;

  v2.position[0] = 1;
  v2.position[1] = -1;
  v2.position[2] = -5;

  v3.position[0] = 1;
  v3.position[1] = 1;
  v3.position[2] = -5;
  _vertices.clear();
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  _vertices.push_back(v3);
  _faces.clear();
  _faces.push_back(0);
  _faces.push_back(1);
  _faces.push_back(2);
  */
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
