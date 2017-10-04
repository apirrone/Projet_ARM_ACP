#include "Voxel.hpp"
#include <iostream>



Voxel::Voxel(double x, double y, double z, double val)
  : _x(x), _y(y), _z(z), _value(val) {
  if(_vef == NULL)
    initVEF();
  for(int i = 0; i<6; ++i)
    _showFace[i] = true;
  _changed = true;
}

void Voxel::initVAO(){

  //create the VAO
  glGenVertexArrays(1,&mVertexArrayId);
  
  
  //vertex buffer
  glGenBuffers(1,&_vertexBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(double)*_vertices.size(), _vertices.data(), GL_STATIC_DRAW);

  //face indices buffer
  glGenBuffers(1,&mIndexBufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector3i)*mFaces.size(), mFaces[0].data(), GL_STATIC_DRAW);
  //TODO peut être mettre GL_DYNAMIC pour si on veut changer à la volée les faces affichées ?
  
  _initialized = true;
  
}

void Voxel::fillVBO(){
  //adds all the vertices and select the faces to show
  
  int e1,e2,e3, v1_1, v1_2, v2_1, v2_2, v3_1, v3_2, v1, v2, v3;
  std::vector<double> * verts = _vef.getVertices();
  std::vector<double> * edges = _vef.getEdges();
  std::vector<double> * faces = _vef.getFaces();

  std::vector<int> faceVertex;
  for(int i = 0; i < 6; ++i){
    if(_showFace[i])
      {
	//for each triangle of the face
	for(int f=0; f<2; ++f){
	  int ind = _faceIndices[i][0];
	  //we retrieve the three edges
	  e1 = (*faces)[ind];
	  e2 = (*faces)[ind+1];
	  e3 = (*faces)[ind+2];

	  //the two vertices of the first edge
	  v1_1 = (*edges)[e1];
	  v1_2 = (*edges)[e1+1];
	  //the two vertices of the second edge
	  v2_1 = (*edges)[e2];
	  v2_2 = (*edges)[e2+1];
	  //the two vertices of the third edge
	  v3_1 = (*edges)[e3];
	  v3_2 = (*edges)[e3+1];

	  //we check which vertex is common between e1 and e2 to determine the order of the vertices
	  if(v1_1 == v2_1){
	    v1 = v1_2;
	    v2 = v1_1;
	    v3 = v2_2;
	  }else if(v1_1 == v2_2){
	    v1 = v1_2;
	    v2 = v1_1;
	    v3 = v2_1;
	  }else if(v1_2 == v2_1){
	    v1 = v1_1;
	    v2 = v1_2;
	    v3 = v2_2;
	  }else if(v1_2 == v2_2){
	    v1 = v1_1;
	    v2 = v1_2;
	    v3 = v2_1;
	  }else{
	    std::cerr << "ERROR Voxel::fillVBO() : broken voxel face (no common vertex between two edges)" << std::endl;
	  }

	  //we check if e3 vertices are correct
	  assert((v3_1 == v3 && v3_2 == v1) || (v3_1 == v1 && v3_2 == v3));

	  //TODO add v1 v2 v3 to openGL face indices array
		  
	}
      }
  }
}


void Voxel::paint(){

  //check if !_initialized -> initVAO
  //check if _changed -> fillVBO
  } 
  
}

void Voxel::initVEF() {
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

  _faceIndices[Voxel::Face::TOP][0] = this->addFace(e3, e4, e13);
  _faceIndices[Voxel::Face::TOP][1] = this->addFace(e1, e2, e13);
  _faceIndices[Voxel::Face::LEFT][0] = this->addFace(e4, e12, e14);
  _faceIndices[Voxel::Face::LEFT][1] = this->addFace(e8, e9, e14);
  _faceIndices[Voxel::Face::FRONT][0] = this->addFace(e1, e9, e15);
  _faceIndices[Voxel::Face::FRONT][1] = this->addFace(e5, e10, e15);
  _faceIndices[Voxel::Face::RIGHT][0] = this->addFace(e2, e10, e16);
  _faceIndices[Voxel::Face::RIGHT][1] = this->addFace(e6, e11, e16);
  _faceIndices[Voxel::Face::BOTTOM][0] = this->addFace(e5, e8, e17);
  _faceIndices[Voxel::Face::BOTTOM][1] = this->addFace(e6, e17, e7);
  _faceIndices[Voxel::Face::REAR][0] = this->addFace(e7, e12, e18);
  _faceIndices[Voxel::Face::REAR][1] = this->addFace(e3, e11, e18);
}
