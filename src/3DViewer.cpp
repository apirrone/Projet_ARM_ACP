#include "3DViewer.hpp"

#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLContext>

Viewer::Viewer(VoxelGrid& grid, QWidget *parent)
  : QOpenGLWidget(parent),
    _voxelGrid(grid)
{
  QSurfaceFormat format;

  format.setVersion(3, 3);

  this->setFormat(format);

  prevPos = QVector2D(0, 0);
  //timer.start(0, this);

  unsigned int w = _voxelGrid.getW();
  unsigned int h = _voxelGrid.getH();
  unsigned int d = _voxelGrid.getD();
  camera = Camera(QVector3D(0., 0., -143), QVector3D(w/2., h/2., d/2.), this->width(), this->height());
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

  f->glEnable(GL_BLEND);
  f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //shader init
  _shader = new QOpenGLShaderProgram();
  _shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "../data/shaders/simple.vert");
  _shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "../data/shaders/simple.frag");
  _shader->link();
  _shader->bind();

}

void Viewer::paintGL(){
  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(0.2, 0.2, 0.2, 1.0);
  f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  _shader->bind();

  _shader->setUniformValue(_shader->uniformLocation("proj_mat"), camera.getProjectionMatrix());
  _shader->setUniformValue(_shader->uniformLocation("view_mat"), camera.getViewMatrix());

  _voxelGrid.draw(_shader);

  _shader->release();

}

void Viewer::resizeGL(int width, int height){

  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glViewport( 0, 0, (GLint)width, (GLint)height );

  camera.updateProjectionMatrix(width, height);

}

void Viewer::mouseMoveEvent(QMouseEvent *e){

  QVector2D diff = QVector2D(e->localPos()) - prevPos;
  QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

  qreal acc = diff.length() / 500.0;

  rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

  angularSpeed += acc;
  prevPos = QVector2D(e->localPos());
}

void Viewer::timerEvent(QTimerEvent *){
  angularSpeed *= 0.97;

  if (angularSpeed < 0.02) {
    angularSpeed = 0.0;
  } else {
    camera.rotateAroundTarget(angularSpeed, rotationAxis);
    update();
  }
}

void Viewer::eventFromParent(QKeyEvent *e){

  if (e->key() == Qt::Key_Escape)
    close();
  else if (e->key() == Qt::Key_Right)
    camera.translateCamera(QVector3D(-1, 0, 0));
  else if (e->key() == Qt::Key_Left)
    camera.translateCamera(QVector3D(1, 0, 0));
  else if (e->key() == Qt::Key_Up)
    camera.translateCamera(QVector3D(0, -1, 0));
  else if (e->key() == Qt::Key_Down)
    camera.translateCamera(QVector3D(0, 1, 0));
  else if (e->key() == Qt::Key_P)
    camera.translateCamera(QVector3D(0, 0, 1));
  else if (e->key() == Qt::Key_L)
    camera.translateCamera(QVector3D(0, 0, -1));
  else if (e->key() == Qt::Key_A)
    camera.rotateAroundTarget(2, QVector3D(0, 1, 0));
  else if (e->key() == Qt::Key_E)
    camera.rotateAroundTarget(-2, QVector3D(0, 1, 0));
  else if (e->key() == Qt::Key_Z)
    camera.zoom(1);
  else if (e->key() == Qt::Key_S)
    camera.zoom(-1);
  else
    QWidget::keyPressEvent(e);

  update();
}
