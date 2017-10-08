#include "3DViewer.hpp"

#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLContext>

Viewer::Viewer(VoxelGrid& grid, QWidget *parent)
  : QOpenGLWidget(parent),
    _voxelGrid(grid)
{
  QSurfaceFormat format;
  //format.setDepthBufferSize(24);
  //format.setStencilBufferSize(8);
  format.setVersion(3, 3);
  //format.setProfile(QSurfaceFormat::CoreProfile);
  this->setFormat(format);
}

Viewer::~Viewer(){
  delete _shader;
}

QSize Viewer::minimumSizeHint() const{
  return QSize(50, 50);
}

QSize Viewer::sizeHint() const{
  return QSize(400, 400);
}

void Viewer::initializeGL(){

  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  
  std::cout << "init" << std::endl;
  f->glClearColor(0.6, 0.2, 0.2, 1.0);

  //shader init
  _shader = new QOpenGLShaderProgram();
  _shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "../data/shaders/simple.vert");
  _shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "../data/shaders/simple.frag");
  _shader->link();

  _projectionMat.setToIdentity();
  _projectionMat.perspective(45.0f, this->width() / float(this->height()), 0.1f, 1000.0f);


  //TODO ajouter camera
  _viewMat.setToIdentity();

  //f->glEnable(GL_DEPTH_TEST);

  // TEMP
  _vertices.clear();
  VEF::Vertex v1, v2, v3;
  v1.position[0] = -0.1;
  v1.position[1] = 0.1;
  v1.position[2] = -5.;
  
  v2.position[0] = -0.1;
  v2.position[1] = -0.1;
  v2.position[2] = -5.;
  
  v3.position[0] = 0.1;
  v3.position[1] = 0.1;
  v3.position[2] = -5.;
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  _vertices.push_back(v3);
  _faces.clear();
  _faces.push_back(0);
  _faces.push_back(1);
  _faces.push_back(2);

  f->glGenBuffers(1, &_vertexBufferId);
  f->glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
  f->glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(VEF::Vertex), _vertices[0].position, GL_STATIC_DRAW); 
  
  f->glGenBuffers(1, &_faceBufferId);
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faceBufferId);
  f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*_faces.size(), _faces.data(), GL_STATIC_DRAW);

  // TEMP
}

void Viewer::paintGL(){

  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(0.2, 0.2, 0.2, 1.0);
  //TODO Récup les voxels et les afficher ici  
  f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  _shader->bind();

  _shader->setUniformValue(_shader->uniformLocation("proj_mat"), _projectionMat);
  //_shader->setUniformValue(_shader->uniformLocation("view_mat"), _viewMat);
  
  //_voxelGrid.draw(_shader);

  //*
  f->glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faceBufferId);

  //position
  int vertex_loc = _shader->attributeLocation("vtx_position");
  if(vertex_loc>=0) {
    //_shader->setAttributeBuffer(vertex_loc, GL_FLOAT, 0, 3, sizeof(VEF::Vertex));
    //_shader->enableAttributeArray(vertex_loc);
    f->glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, sizeof(VEF::Vertex), (void*)0);
    f->glEnableVertexAttribArray(vertex_loc);
  }
  //f->glDrawArrays(GL_TRIANGLES, 0, 6);
  f->glDrawElements(GL_TRIANGLES, _faces.size(), GL_UNSIGNED_INT, 0);
  if(vertex_loc)
    f->glDisableVertexAttribArray(vertex_loc);
    //_shader->disableAttributeArray(vertex_loc);
  
  //*/
  _shader->release();

  
}

void Viewer::resizeGL(int width, int height){

  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glViewport( 0, 0, (GLint)width, (GLint)height );
  _projectionMat.setToIdentity();
  _projectionMat.perspective(45.0f, width / float(height), 0.1f, 1000.0f);
}

