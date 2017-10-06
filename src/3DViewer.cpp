#include "3DViewer.hpp"

Viewer::Viewer(VoxelGrid& grid, QWidget *parent)
  : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    _voxelGrid(grid)
{
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
  glClearColor(0.6, 0.2, 0.2, 1.0);

  //shader init
  _shader = new QOpenGLShaderProgram();
  _shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "../data/shaders/simple.vert");
  _shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "../data/shaders/simple.frag");
  _shader->link();

  _projectionMat.setToIdentity();
  _projectionMat.perspective(45.0f, this->width() / float(this->height()), 0.1f, 1000.0f);

  _viewMat.setToIdentity();

  
  glEnable(GL_DEPTH_TEST);
}

void Viewer::paintGL(){
  
  //TODO Récup les voxels et les afficher ici  
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  _shader->bind();

  _shader->setUniformValue(_shader->uniformLocation("proj_mat"), _projectionMat);
  _shader->setUniformValue(_shader->uniformLocation("view_mat"), _viewMat);
  
  _voxelGrid.draw(_shader);

  _shader->release();

  
}

void Viewer::resizeGL(int width, int height){

  //glViewport( 0, 0, (GLint)width, (GLint)height );
  _projectionMat.setToIdentity();
  _projectionMat.perspective(45.0f, width / float(height), 0.1f, 1000.0f);
}

