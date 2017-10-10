#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>
#include <regex>
#include <sstream>

#include "VEF.hpp"

using namespace std;

vector<string> split(const string &s, char delim) {
  
  stringstream ss(s);
  string item;
  vector<string> tokens;
  
  while (getline(ss, item, delim))
    tokens.push_back(item);
  
  return tokens;
  
}

void VEF::loadFromObj(char* filePath){
  string line;
  ifstream fileToRead(filePath);  

  if (fileToRead.is_open()) {

    vector<float*> tmpNormals;

    while(getline(fileToRead, line)){
      char firstChar = line.at(0);

      if(firstChar == '#') // Ignore comments
	continue;
      

      vector<string> tokens = split(line, ' ');

      if(tokens.at(0).compare("v") == 0){
	double x = stod(tokens.at(1));
	double y = stod(tokens.at(2));
	double z = stod(tokens.at(3));
	cout << "x : " << x << ", y : " << y << ", z : " << z << std::endl;
	this->addVertex(x, y, z);
      }
      
      
      if(tokens.at(0).compare("vn") == 0){
	float x = stod(tokens.at(1));
	float y = stod(tokens.at(2));
	float z = stod(tokens.at(3));
	  
	float n[3];
	n[0] = x;
	n[1] = y;
	n[2] = z;
	tmpNormals.push_back(n);
      }

      if(tokens.at(0).compare("f") == 0){
	  
	vector<string> vertexToken;
	  
	bool convertIntoTriangleFace = false;

	int nbVertex = tokens.size()-1;//not taking into account the f at beggining
	if(nbVertex > 3)//Triangle face
	  convertIntoTriangleFace = true;
	  
	int *vertexIds;
	  
	if(convertIntoTriangleFace)
	  vertexIds = (int*)malloc((nbVertex)*sizeof(int));
	else
	  vertexIds = (int*)malloc(3*sizeof(int));

	  
	for(int i = 1 ; i < tokens.size() ; i++){
	  vertexToken = split(tokens.at(i), '/');

	  if(vertexToken.size() != 3){
	    cerr << "Incorrect face definition : " << tokens.at(i) << endl;
	    fileToRead.close();
	    return;
	  }

	  int vertexId = stoi(vertexToken.at(0))-1;//Indices in .obj start at 1
	  int normalId = stoi(vertexToken.at(2))-1;

	  if(this->getVertices()->at(vertexId).normalSet == false){// This vertex normals has not been set yet
	    
	    this->getVertices()->at(vertexId).normal[0] = tmpNormals.at(normalId)[0];
	    this->getVertices()->at(vertexId).normal[1] = tmpNormals.at(normalId)[1];
	    this->getVertices()->at(vertexId).normal[2] = tmpNormals.at(normalId)[2];

	    vertexIds[i-1] = vertexId;

	    this->getVertices()->at(vertexId).normalSet = true;
	  }
	  else{

	    if(this->getVertices()->at(vertexId).normal[0] != tmpNormals.at(normalId)[0] &&
	       this->getVertices()->at(vertexId).normal[1] != tmpNormals.at(normalId)[1] &&
	       this->getVertices()->at(vertexId).normal[2] != tmpNormals.at(normalId)[2]){
		
	      //We have to duplicate the vertex
		
	      double x = this->getVertices()->at(vertexId).position[0];
	      double y = this->getVertices()->at(vertexId).position[1];
	      double z = this->getVertices()->at(vertexId).position[2];
		
	      int newVertexId = this->addVertex(x, y, z);
		
	      this->getVertices()->at(newVertexId).normal[0] = tmpNormals.at(normalId)[0];
	      this->getVertices()->at(newVertexId).normal[1] = tmpNormals.at(normalId)[1];
	      this->getVertices()->at(newVertexId).normal[2] = tmpNormals.at(normalId)[2];
		
	      vertexIds[i-1] = newVertexId;
	      this->getVertices()->at(newVertexId).normalSet = true;
	    }
	    else//The vertex with the same normal already exists
	      vertexIds[i-1] = vertexId;		
	  }
	}

	  
	if(convertIntoTriangleFace){
	  cout << "coucou" << endl;
	  for(int k = 0 ; k < nbVertex-1 ; k++){
	    this->addFace(vertexIds[0],
			  vertexIds[k],
			  vertexIds[k+1]);	      
	  }
	}
	else{
	  this->addFace(vertexIds[0],
			vertexIds[1],
			vertexIds[2]);
	} 
      }
    }//end while
    
    fileToRead.close();
  }
  else {
    // file could not be opened 
    cerr << "The file : " << filePath <<" could not be opened" << endl;
    return;
  }
  //*/
  

  std::cout << "VEF vertices : " << std::endl;
  for(int i=0; i < _vertices.size(); ++i)
    std::cout << "\tv" << i << " " << _vertices[i].toString();

}

void VEF::exportToObj(char* exportFilePath){
  //TODO To be implemented
}

void VEF::draw(QOpenGLShaderProgram* shader){
  // std::cout << "DRAW VEF" << std::endl;

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

void VEF::initVAO() {
  std::cout << "VEF initVAO" << std::endl;
  _vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  std::cout << "VEF initVAO 1" << std::endl;
  _vertexBuffer->create();
  _vertexBuffer->bind();
  _vertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
  _vertexBuffer->allocate(&(_vertices[0]), sizeof(VEF::Vertex)*_vertices.size());
  std::cout << "VEF initVAO 2" << std::endl;
  _indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  _indexBuffer->create();
  _indexBuffer->bind();
  _indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
  _indexBuffer->allocate(&(_faces[0]), sizeof(unsigned int)*_faces.size());
  std::cout << "VEF initVAO 3" << std::endl;
  _vertexArray.create();
  std::cout << "VEF initVAO 4" << std::endl;
  _initialized = true;

}

// getters
std::vector<VEF::Vertex>* VEF::getVertices() {
  return &_vertices;
}

std::vector<unsigned int>* VEF::getEdges() {
  return &_edges;
}

std::vector<unsigned int>* VEF::getFaces() {
  return &_faces;
}

// setters
//add an element and returns its index in the VEF
int VEF::addVertex(const VEF::Vertex& v) {
  int id = _vertices.size();
  _vertices.push_back(v);
  return id;
}

int VEF::addVertex(double x, double y, double z) {
  int id = _vertices.size();
  _vertices.push_back(Vertex(x, y, z));
  return id;
}

int VEF::addEdge(int p1, int p2) {
  int id = _edges.size();
  _edges.push_back(p1);
  _edges.push_back(p2);
  return id;
}

int VEF::addFace(int e1, int e2, int e3) {
  int id = _faces.size();
  _faces.push_back(e1);
  _faces.push_back(e2);
  _faces.push_back(e3);
  return id;
}

unsigned int VEF::getW(){
  return _w;
}

unsigned int VEF::getH(){
  return _h;
}

unsigned int VEF::getD(){
  return _d;
}
