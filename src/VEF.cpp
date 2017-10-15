#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <map>
#include <set>

#include "VEF.hpp"

using namespace std;

//Splits string using delimiter
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

void removeMultipleSpaces(string& s){
  char p;

  for(int i = 0 ; i < s.size() ; i++){

    p = s[i];
    int iStart = i;

    while(p == ' ' && p != '\0'){
      i++;
      p = s[i];
    }

    if(i - iStart > 1)
      s.erase(iStart, (i - iStart)-1);

  }
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

    size_t maxVerts = 4;
    unsigned int* faceVertices = new unsigned int[maxVerts];

    map<std::pair<unsigned int, unsigned int>, unsigned int> objVertices;
    vector<float> objPositions;
    vector<float> objNormals;

    Vertex v;

    //Parse file line by line
    while(getline(fileToRead, line)){

      removeMultipleSpaces(line);

      //Ignore empty lines
      if(line.size() == 0)
	continue;

      //Get elements of the string delimited by a space
      vector<string> tokens = split(line, ' ');


      if(tokens.at(0).compare("v") == 0){ //Add vertices

	double x = stod(tokens.at(1));
	double y = stod(tokens.at(2));
	double z = stod(tokens.at(3));

	objPositions.push_back(x);
	objPositions.push_back(y);
	objPositions.push_back(z);
      }
      else if(tokens.at(0).compare("vn") == 0){ //Add vertices normals

	float x = stod(tokens.at(1));
	float y = stod(tokens.at(2));
	float z = stod(tokens.at(3));

	objNormals.push_back(x);
	objNormals.push_back(y);
	objNormals.push_back(z);
      }
      else if(tokens.at(0).compare("f") == 0){ //Add and create faces
	vector<string> vertexToken;

	int nbVertex = tokens.size()-1;//not taking into account the f at beggining

	if (nbVertex > maxVerts) {
	  maxVerts *= 2;
	  delete[] faceVertices;
	  faceVertices = new unsigned int[maxVerts];
	}

	for(int i = 1 ; i < tokens.size() ; i++){

	  vertexToken = split(tokens.at(i), '/');

	  bool hasNormals = false;
	  if(vertexToken.size() < 1 || vertexToken.size() > 3){
	    cerr << "Incorrect face definition : " << tokens.at(i) << endl;
	    fileToRead.close();
	    return;
	  }
	  else if (vertexToken.size() == 3) {
	    hasNormals = true;
	  }

	  int vertexId = stoi(vertexToken.at(0));//Indices in .obj start at 1
	  int normalId;

	  if(hasNormals)
	    normalId = stoi(vertexToken.at(2));
	  else
	    normalId = 0;

	  unsigned int vID;
	  if (vID = objVertices.find(std::pair<unsigned int, unsigned int>(vertexId, normalId)) != objVertices.end()) {
	    // no need to create a new vertex
	    faceVertices[i-1] = vID;
	  }
	  else {
	    // we create a new vertex
	    float vX = objPositions[(vertexId-1)*3];
	    float vY = objPositions[(vertexId-1)*3+1];
	    float vZ = objPositions[(vertexId-1)*3+2];

	    v.position[0] = vX;
	    v.position[1] = vY;
	    v.position[2] = vZ;

	    if(hasNormals) {
	      v.normal[0] = objNormals[(normalId-1)*3];
	      v.normal[1] = objNormals[(normalId-1)*3+1];
	      v.normal[2] = objNormals[(normalId-1)*3+2];
	      v.normalSet = true;
	    }
	    else
	      v.normalSet = false;


	    faceVertices[i-1] = this->addVertex(v);
	  }
	} // end for

	for(int k = 1 ; k < nbVertex-1 ; k++){
	  this->addFace(faceVertices[0],
			faceVertices[k],
			faceVertices[k+1]);
	}

      } // end face builder

    }//end while

    fileToRead.close();

    // clean
    delete[] faceVertices;

  }
  else {
    // file could not be opened
    cerr << "The file : " << filePath <<" could not be opened" << endl;
    return;
  }

  double miny2 = 1000., maxy2 = -1000.;

  for(int i = 0; i<_vertices.size(); ++i){

    double y = _vertices[i].position[1];

    if(y < miny2)
      miny2 = y;
    if(y > maxy2)
      maxy2 = y;

  }

}

void VEF::exportToObj(std::string exportFilePath){

  if(_vertices.size() == 0)
    return;

  ofstream output;
  output.open(exportFilePath);

  output << "# Obj file generated by VisioBrain software" << endl;
  output << "# Written by Guillaume Almyre, Pierre Célor and Antoine Pirrone" << endl;

  //Write vertices
  for(auto v : _vertices)
    output << "v " << v.position[0] << " " << v.position[1] << " " << v.position[2] << endl;

  //Write vertices normals
  for(auto v : _vertices)
    output << "vn " << v.normal[0] << " " << v.normal[1] << " " << v.normal[2] << endl;

  //Write faces
  for(int f = 0 ; f < _faces.size() ; f+=3){
    unsigned int v1 = _faces.at(f)+1;
    unsigned int v2 = _faces.at(f+1)+1;
    unsigned int v3 = _faces.at(f+2)+1;

    output << "f " << v1 << "//" << v1 << " " << v2 << "//" << v2 << " " << v3 << "//" << v3 << endl;
  }

  output.close();
}

void VEF::draw(QOpenGLShaderProgram* shader){

  if(!_initialized)
    initVAO();

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
}

void VEF::loadSurfaceMesh() {
  _surfaceMesh.clear();

  vector<surface_mesh::Surface_mesh::Vertex> vertexId;

  for(int i = 0; i<_vertices.size(); ++i) {

    Vertex& v = _vertices[i];
    surface_mesh::Surface_mesh::Vertex vid = _surfaceMesh.add_vertex(surface_mesh::Point(v.position[0], v.position[1], v.position[2]));
    vertexId.push_back(vid);

  }

  for(int i = 0; i<_faces.size(); i+=3) {

    surface_mesh::Surface_mesh::Vertex v1, v2, v3;

    v1 = vertexId[_faces[i]];
    v2 = vertexId[_faces[i+1]];
    v3 = vertexId[_faces[i+2]];

    _surfaceMesh.add_triangle(v1, v2, v3);

  }

  _surfaceMesh.write("testExportOFF.off");
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

int VEF::addVertex(float x, float y, float z) {
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
