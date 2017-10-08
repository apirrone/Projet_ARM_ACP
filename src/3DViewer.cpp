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


  _viewMat.setToIdentity();
  _viewMat.lookAt(QVector3D(0,0,5), QVector3D(0,0,0), QVector3D(0,1,0));
}

void Viewer::paintGL(){

  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(0.2, 0.2, 0.2, 1.0);
  f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  _shader->bind();

  _shader->setUniformValue(_shader->uniformLocation("proj_mat"), _projectionMat);
  _shader->setUniformValue(_shader->uniformLocation("view_mat"), _viewMat);

  _voxelGrid.draw(_shader);
  
  _shader->release();

  
}

void Viewer::resizeGL(int width, int height){

  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glViewport( 0, 0, (GLint)width, (GLint)height );
  _projectionMat.setToIdentity();
  _projectionMat.perspective(45.0f, width / float(height), 0.1f, 1000.0f);
}

