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

VEF::VEF()
  : _position(QVector3D(0,0,0)), _initialized(false), _updateWorldMat(true) {}

VEF::~VEF() {
  if(_vertexBuffer != NULL){
    _vertexBuffer->destroy();
    delete _vertexBuffer;
  }
  if(_indexBuffer != NULL){
    _indexBuffer->destroy();
    delete _indexBuffer;
  }

  _vertexArray.destroy();
  
}

void VEF::loadFromObj(std::string filePath){
  std::setlocale(LC_ALL, "C"); // IMPORTANT !!!!
  string line;
  ifstream fileToRead(filePath);
  int ln = 0;
  double miny = 1000., maxy=-1000.;
  _vertices.clear();
  _faces.clear();

  if (fileToRead.is_open()) {
    vector<Vertex> tmpVertices;
    vector<float> tmpNormals;

    while(getline(fileToRead, line)){

      
      line = regex_replace(line, regex("\\s+"), " ");

      if(line.size() == 0 || line[0] == '#') // Ignore comments
	continue;
      
      vector<string> tokens = split(line, ' ');
      
      if(tokens.at(0).compare("v") == 0){
	// cout << "ADD VERTEX " << endl;
	//cout << line << endl;

	double x = stod(tokens.at(1));
	double y = stod(tokens.at(2));
	double z = stod(tokens.at(3));
	Vertex v = Vertex(x,y,z);
	if(y < miny)
	  miny = y;
	if(y > maxy)
	  maxy = y;
	//cerr << "v " << x << " " << y << " " << z << endl;
	//this->addVertex(x, y, z);
	ln++;
	tmpVertices.push_back(v);
      }
      else if(tokens.at(0).compare("vn") == 0){
	// cout << "ADD NORMAL " << endl;

	float x = stod(tokens.at(1));
	float y = stod(tokens.at(2));
	float z = stod(tokens.at(3));

	tmpNormals.push_back(x);
	tmpNormals.push_back(y);
	tmpNormals.push_back(z);
      }
      else if(tokens.at(0).compare("f") == 0){
	// cout << "ADD FACE " << endl;
	//std::cout << line << std::endl;
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
	//std::cerr << "f ";
	for(int i = 1 ; i < tokens.size() ; i++){
	  
	  vertexToken = split(tokens.at(i), '/');

	  if(vertexToken.size() != 3){
	    cerr << "Incorrect face definition : " << tokens.at(i) << endl;
	    fileToRead.close();
	    return;
	  }
	  //std::cerr << stoi(vertexToken[0]) << "//" << stoi(vertexToken[2]) << " ";

	  int vertexId = stoi(vertexToken.at(0))-1;//Indices in .obj start at 1
	  int normalId = (stoi(vertexToken.at(2))-1)*3;
	  /*
	  if(this->getVertices()->at(vertexId).normalSet == false){// This vertex normals has not been set yet
	    
	    this->getVertices()->at(vertexId).normal[0] = tmpNormals.at(normalId);
	    this->getVertices()->at(vertexId).normal[1] = tmpNormals.at(normalId+1);
	    this->getVertices()->at(vertexId).normal[2] = tmpNormals.at(normalId+2);

	    vertexIds[i-1] = vertexId;

	    this->getVertices()->at(vertexId).normalSet = true;
	  }
	  else{

	    if(this->getVertices()->at(vertexId).normal[0] != tmpNormals.at(normalId) ||
	       this->getVertices()->at(vertexId).normal[1] != tmpNormals.at(normalId+1) ||
	       this->getVertices()->at(vertexId).normal[2] != tmpNormals.at(normalId+2)){

	      //We have to duplicate the vertex

	      double x = this->getVertices()->at(vertexId).position[0];
	      double y = this->getVertices()->at(vertexId).position[1];
	      double z = this->getVertices()->at(vertexId).position[2];

	      int newVertexId = this->addVertex(x, y, z);
	      
	      this->getVertices()->at(newVertexId).normal[0] = tmpNormals.at(normalId);
	      this->getVertices()->at(newVertexId).normal[1] = tmpNormals.at(normalId+1);
	      this->getVertices()->at(newVertexId).normal[2] = tmpNormals.at(normalId+2);

	      vertexIds[i-1] = newVertexId;
	      this->getVertices()->at(newVertexId).normalSet = true;
	    }
	    else{//The vertex with the same normal already exists
	      vertexIds[i-1] = vertexId;
	    }

	  }
	  */
	
	  
	  Vertex v = tmpVertices[vertexId];
	  v.normal[0] = tmpNormals[normalId];
	  v.normal[1] = tmpNormals[normalId+1];
	  v.normal[2] = tmpNormals[normalId+2];
	  vertexIds[i-1] = this->addVertex(v);
	}
	if(convertIntoTriangleFace){
	  for(int k = 1 ; k < nbVertex-1 ; k++){
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

	free(vertexIds);
      }
    }//end while

    fileToRead.close();
  }
  else {
    // file could not be opened
    cerr << "The file : " << filePath <<" could not be opened" << endl;
    return;
  }
  //std::cout << ln << std::endl;
  double miny2 = 1000., maxy2 = -1000.;
  for(int i = 0; i<_vertices.size(); ++i){
    double y = _vertices[i].position[1];
    if(y < miny2)
      miny2 = y;
    if(y > maxy2)
      maxy2 = y;
  }
  std::cout << miny << " " << maxy<< " " << miny2 << " " << maxy2 << std::endl;
}

void VEF::exportToObj(char* exportFilePath){

  if(_vertices.size() == 0)
    return;

  ofstream output;
  output.open(exportFilePath);

  output << "# Obj file generated by VisioBrain software" << endl;
  output << "# Written by Guillaume Almyre, Pierre Célor and Antoine Pirrone" << endl;

  for(auto v : _vertices){
    output << "v " << v.position[0] << " " << v.position[1] << " " << v.position[2] << endl;
  }

  for(auto v : _vertices){
    output << "vn " << v.normal[0] << " " << v.normal[1] << " " << v.normal[2] << endl;
  }

  for(int f = 0 ; f < _faces.size() ; f+=3){
    unsigned int v1 = _faces.at(f)+1;
    unsigned int v2 = _faces.at(f+1)+1;
    unsigned int v3 = _faces.at(f+2)+1;

    output << "f " << v1 << "//" << v1 << " " << v2 << "//" << v2 << " " << v3 << "//" << v3 << endl;
  }

  output.close();
}

void VEF::draw(QOpenGLShaderProgram* shader){
  //std::cout << "DRAW VEF" << std::endl;

  if(!_initialized)
    initVAO();
  

  QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();

  shader->setUniformValue(shader->uniformLocation("world_mat"), this->worldMatrix());
  _vertexArray.bind();
  _vertexBuffer->bind();
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

  if(vertex_loc)
    shader->disableAttributeArray(vertex_loc);
  if(color_loc)
    shader->disableAttributeArray(color_loc);
    
  _indexBuffer->release();
  _vertexBuffer->release();
  _vertexArray.release();

}

void VEF::initVAO() {
  std::cout <<"INIT VAO"<< std::endl;
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
  _indexBuffer->release();
  _vertexBuffer->release();

  //for(int i = 0; i < _vertices.size(); ++i)
  //std::cout << "vert " << i << " " << _vertices[i].toString() << std::endl;

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

void VEF::translate(QVector3D t) {
  _updateWorldMat = true;
  _position += t;
}

QMatrix4x4 VEF::worldMatrix() {
  if(!_updateWorldMat)
    return _worldMat;
  _worldMat.setToIdentity();
  _worldMat.translate(_position);
  return _worldMat;
}
