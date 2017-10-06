#include <QOpenGLShaderProgram>
#include <iostream>

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
	std::cout << "test" << std::endl;
	VEF::Vertex v;
	//we create all the vertices
	//TFL
	v = VEF::Vertex(i-0.5f, j+0.5f, k+0.5f);
	current.vertices[Voxel::Corner::TFL] = this->addVertex(v);
	//TFR
	v = VEF::Vertex(i+0.5f, j+0.5f, k+0.5f);
	current.vertices[Voxel::Corner::TFR] = this->addVertex(v);
	//TRL
	v = VEF::Vertex(i-0.5f, j+0.5f, k-0.5f);
	current.vertices[Voxel::Corner::TRL] = this->addVertex(v);
	//TRR
	v = VEF::Vertex(i+0.5f, j+0.5f, k-0.5f);
	current.vertices[Voxel::Corner::TRR] = this->addVertex(v);
	//BFL
	v = VEF::Vertex(i-0.5f, j-0.5f, k+0.5f);
	current.vertices[Voxel::Corner::BFL] = this->addVertex(v);
	//BFR
	v = VEF::Vertex(i+0.5f, j-0.5f, k+0.5f);
	current.vertices[Voxel::Corner::BFR] = this->addVertex(v);
	//BRL
	v = VEF::Vertex(i-0.5f, j-0.5f, k-0.5f);
	current.vertices[Voxel::Corner::BRL] = this->addVertex(v);
	//BRR
	v = VEF::Vertex(i+0.5f, j-0.5f, k-0.5f);
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
	  this->addFace(current.vertices[Voxel::Corner::TRR],
			current.vertices[Voxel::Corner::TRL],
			current.vertices[Voxel::Corner::BRL]);
	  this->addFace(current.vertices[Voxel::Corner::TRR],
			current.vertices[Voxel::Corner::BRL],
			current.vertices[Voxel::Corner::BRR]);
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


  _vertexBufferId.destroy();
  _vertexArrayId.destroy();
}

void VoxelGrid::draw(QOpenGLShaderProgram* shader){
  if(!_initialized)
   initVAO();
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  glEnableClientState(GL_VERTEX_ARRAY);

  _vertexArrayId.bind();
  _vertexBufferId.bind();
  //_vertexFaceId.bind();

  //position
  int vertex_loc = shader->attributeLocation("vtx_position");
  if(vertex_loc>=0) {
    shader->setAttributeBuffer(vertex_loc, GL_FLOAT, 0, 3, sizeof(VEF::Vertex));
    shader->enableAttributeArray(vertex_loc);
  }

  //normal
  int normal_loc = shader->attributeLocation("vtx_normal");
  if(normal_loc>=0) {
    shader->setAttributeBuffer(normal_loc, GL_FLOAT, sizeof(float) * 3, 3, sizeof(VEF::Vertex));
    shader->enableAttributeArray(normal_loc);
  }

  //color
  int color_loc = shader->attributeLocation("vtx_color");
  if(color_loc>=0) {
    shader->setAttributeBuffer(color_loc, GL_FLOAT, sizeof(float)*6, 4, sizeof(VEF::Vertex));
    shader->enableAttributeArray(color_loc);
  }

  _vertexBufferId.release();

  _vertexFaceId.bind();
  
  //draw
  //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  if(vertex_loc)
    shader->disableAttributeArray(vertex_loc);
  if(normal_loc)
    shader->disableAttributeArray(normal_loc);
  if(color_loc)
    shader->disableAttributeArray(color_loc);

  _vertexFaceId.release();
  //_vertexBufferId.release();
  _vertexArrayId.release();

  glDisableClientState(GL_VERTEX_ARRAY);

}

void VoxelGrid::initVAO() {
  _vertexBufferId.create();
  _vertexBufferId.bind();
  _vertexBufferId.setUsagePattern(QOpenGLBuffer::StaticDraw);
  //DEBUG
  _vertices.clear();
  Vertex v1, v2, v3;
  v1.position[0] = -1.;
  v1.position[1] = 0.;
  v1.position[2] = -5.;
  
  v2.position[0] = 1.;
  v2.position[1] = 0.;
  v2.position[2] = -5.;
  
  v3.position[0] = 0.;
  v3.position[1] = 1.;
  v3.position[2] = -5.;
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  _vertices.push_back(v3);
  _faces.clear();
  _faces.push_back(0);
  _faces.push_back(1);
  _faces.push_back(2);
  //END DEBUG


  _vertexBufferId.allocate(_vertices.data(), sizeof(VEF::Vertex) * _vertices.size());

  _vertexFaceId = QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
  _vertexFaceId.bind();
  _vertexFaceId.setUsagePattern(QOpenGLBuffer::StaticDraw);
  _vertexFaceId.allocate(_faces.data(), sizeof(int)*_faces.size());

  _vertexArrayId.create();

  _vertexFaceId.release();
  _vertexBufferId.release();

  for(int i = 0; i<_vertices.size(); ++i)
    std::cout << "vert : " << i << " -> " << _vertices[i].position[0] << " " << _vertices[i].position[1] << " " << _vertices[i].position[2] << std::endl;

  _initialized = true;
  //_vertexArrayId.bind();
  

  /*
  //create our VAO and bind it
  glGenVertexArrays(1, &_vertexArrayId);
  glBindVertexArray(_vertexArrayId);

  glGenBuffers(1, &_vertexBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
  glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(VEF::Vertex), _vertices[0].position, GL_STATIC_DRAW); 
  
  glGenBuffers(1, &_vertexFaceId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexBufferId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*_faces.size(), _faces[0], GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  */
}

