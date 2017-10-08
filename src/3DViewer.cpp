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
  f->glEnable(GL_CULL_FACE);
  //shader init
  _shader = new QOpenGLShaderProgram();
  _shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "../data/shaders/simple.vert");
  _shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "../data/shaders/simple.frag");
  _shader->link();
  _shader->bind();

  _projectionMat.setToIdentity();
  _projectionMat.perspective(45.0f, this->width() / float(this->height()), 0.1f, 1000.0f);


  //TODO ajouter camera
  _viewMat.setToIdentity();
  _viewMat.lookAt(QVector3D(0,0,5), QVector3D(0,0,0), QVector3D(0,1,0));
  

  //f->glEnable(GL_DEPTH_TEST);

  // TEMP
  _vertices[0] = -1;
  _vertices[1] = -1;
  _vertices[2] = -5;

  _vertices[3] = 1;
  _vertices[4] = -1;
  _vertices[5] = -5;

  _vertices[6] = 1;
  _vertices[7] = 1;
  _vertices[8] = -5;

  _faces[0] = 0;
  _faces[1] = 1;
  _faces[2] = 2;
  
  /*
  f->glGenBuffers(1, &_vertexBufferId);
  f->glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
  f->glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), _vertices, GL_STATIC_DRAW); 
  
  f->glGenBuffers(1, &_faceBufferId);
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faceBufferId);
  f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*3, _faces, GL_STATIC_DRAW);
  */

  _vertexBufferId.create();
  _vertexBufferId.bind();
  _vertexBufferId.setUsagePattern(QOpenGLBuffer::StaticDraw);
  _vertexBufferId.allocate(_vertices, sizeof(float)*9);

  _faceBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  _faceBuffer->create();
  _faceBuffer->bind();
  _faceBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
  _faceBuffer->allocate(_faces, sizeof(unsigned int)*3);
    
  _object.create();
  _object.bind();

  int vertex_loc = _shader->attributeLocation("vtx_position");
  if(vertex_loc>=0) {
    _shader->setAttributeBuffer(vertex_loc, GL_FLOAT, 0, 3, sizeof(float)*3);
    _shader->enableAttributeArray(vertex_loc);
    //f->glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //f->glEnableVertexAttribArray(vertex_loc);
  }
  
  // TEMP
  _object.release();
  _vertexBufferId.release();
  _shader->release();
}

void Viewer::paintGL(){

  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(0.2, 0.2, 0.2, 1.0);
  //TODO Récup les voxels et les afficher ici  
  f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  _shader->bind();

  _shader->setUniformValue(_shader->uniformLocation("proj_mat"), _projectionMat);
  _shader->setUniformValue(_shader->uniformLocation("view_mat"), _viewMat);
  
  //_voxelGrid.draw(_shader);

  //*
  //f->glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
  //f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faceBufferId);
  _object.bind();
  _faceBuffer->bind();
  //glDrawArrays(GL_TRIANGLES, 0, 3);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
  _object.release();
  /*
  //position
  int vertex_loc = _shader->attributeLocation("vtx_position");
  if(vertex_loc>=0) {
    std::cout << "aaaaaaaaaaaaaaah" << std::endl;
    //_shader->setAttributeBuffer(vertex_loc, GL_FLOAT, 0, 3, sizeof(VEF::Vertex));
    //_shader->enableAttributeArray(vertex_loc);
    f->glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(vertex_loc);
  }
  //f->glDrawArrays(GL_TRIANGLES, 0, 6);
  f->glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
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

