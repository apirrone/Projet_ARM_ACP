#include "Voxel.hpp"
#include <iostream>

static initVEF() {
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

static fillVBO(){
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

Voxel::Voxel(double x, double y, double z, double val)
  : _x(x), _y(y), _z(z), _value(val) {
  if(_vef == NULL)
    initVEF();
  for(int i = 0; i<6; ++i)
    _showFace[i] = true;
  _changed = true;
}

void Voxel::initVBA(){

  //vertex VBO
  glGenBuffers(1,&_vertexBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(double)*_vertices.size(), _vertices.data(), GL_STATIC_DRAW);
  
  glGenBuffers(1,&mIndexBufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector3i)*mFaces.size(), mFaces[0].data(), GL_STATIC_DRAW);
  //TODO peut être mettre GL_DYNAMIC pour si on veut changer à la volée les faces affichées ?
  
  glGenVertexArrays(1,&mVertexArrayId);
  
  mIsInitialized = true;
  
  glClearColor(0.8, 0.8, 0.8, 1);
}

void Voxel::paint(){
  //TODO check _changed
  int val = _value/255;
  
  // glColor3f(val,val,val);  
  glColor3f(1, 0, 0);  

  for(int i = 9 ; i < 12 ; i+=3){

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

    std::cout << "v1_x : " << v1_x << ", v1_y : " << v1_y << ", v1_z : " << v1_z << std::endl;
    std::cout << "v2_x : " << v2_x << ", v2_y : " << v2_y << ", v2_z : " << v2_z << std::endl;
    std::cout << "v3_x : " << v3_x << ", v3_y : " << v3_y << ", v3_z : " << v3_z << std::endl;

    // std::cout << "v4_x : " << v4_x << ", v4_y : " << v4_y << ", v4_z : " << v4_z << std::endl;
    // std::cout << "v5_x : " << v5_x << ", v5_y : " << v5_y << ", v5_z : " << v5_z << std::endl;
    // std::cout << "v6_x : " << v6_x << ", v6_y : " << v6_y << ", v6_z : " << v6_z << std::endl;
    
    glVertex3f(v1_x, v1_y, v1_z);
    glVertex3f(v2_x, v2_y, v2_z);
    glVertex3f(v3_x, v3_y, v3_z);

    // glVertex3f(v4_x, v4_y, v4_z);
    // glVertex3f(v5_x, v5_y, v5_z);
    // glVertex3f(v6_x, v6_y, v6_z);
  } 
  
}
