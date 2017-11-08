#include "Viewer.hpp"

#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLContext>

Viewer::Viewer(QWidget *parent)
  : QOpenGLWidget(parent)
{
  QSurfaceFormat format;
  format.setVersion(3, 3);

  this->setFormat(format);

  _track = false;
  _move = false;
  _prevPos = QVector2D(0, 0);
  _timer.start(0, this);
  _vef = NULL;//new VEF();
}

Viewer::Viewer(VEF& grid, QWidget *parent)
  : QOpenGLWidget(parent),
    _vef(&grid)
{
  QSurfaceFormat format;

  format.setVersion(3, 3);

  this->setFormat(format);

  _track = false;
  _move = false;
  _prevPos = QVector2D(0, 0);
  _timer.start(0, this);

}

Viewer::~Viewer(){
  delete _shader;
}

void Viewer::setVEF(VEF& vef) {
  if(_vef != NULL)
    delete _vef;
  _vef = &vef;
}

VEF* Viewer::getVEF() {
  return _vef;
}

QSize Viewer::minimumSizeHint() const{
  return QSize(50, 50);
}

QSize Viewer::sizeHint() const{
  return QSize(400, 400);
}

void Viewer::initializeGL(){

  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();

  f->glClearColor(0.6, 0.2, 0.2, 1.0);
  f->glEnable(GL_CULL_FACE);
  f->glEnable(GL_BLEND);
  f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPolygonMode(GL_FRONT, GL_LINE);

  //shader init
  _shader = new QOpenGLShaderProgram();
  _shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "../data/shaders/simple.vert");
  _shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "../data/shaders/simple.frag");
  _shader->link();
  _shader->bind();

  _camera.initCamera(300, 0, 0, QVector3D(0., 0., 0.), this->width(), this->height(), 45.);
  _shader->release();
  _track = false;
  _move = false;
}

void Viewer::paintGL(){

  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(0.2, 0.2, 0.2, 1.0);
  f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  _shader->bind();
  _shader->setUniformValue(_shader->uniformLocation("proj_mat"), _camera.projectionMatrix());
  _shader->setUniformValue(_shader->uniformLocation("view_mat"), _camera.viewMatrix());
  if(_vef)
    _vef->draw(_shader);
  _shader->release();
}

void Viewer::resizeGL(int width, int height){
  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glViewport( 0, 0, (GLint)width, (GLint)height );
  _camera.setViewPort(width, height);
}

void Viewer::mousePressEvent(QMouseEvent *e){

  if(e->buttons() == Qt::LeftButton){
    _track = true;
    _prevPos = QVector2D(e->localPos());
  }
  else if(e->buttons() == Qt::MidButton){
    _move = true;
    _prevPos = QVector2D(e->localPos());
  }
  else
    e->ignore();
}

void Viewer::mouseReleaseEvent(QMouseEvent *e){
  _track = false;
  _move = false;
}

void Viewer::mouseMoveEvent(QMouseEvent *e){

  if(_track){
    QVector2D diff = QVector2D(e->localPos()) - _prevPos;
    _camera.rotateLongitude((-diff.x())/10);
    _camera.rotateLatitude((-diff.y())/10);
  }
  else if (_move){
    QVector2D diff = QVector2D(e->localPos()) - _prevPos;

    _vef->translate(QVector3D(diff.x(),-diff.y(),0)*0.005);
  }
  else
    e->ignore();

  _prevPos = QVector2D(e->localPos());
}

void Viewer::wheelEvent(QWheelEvent *e){
  (e->delta() > 0) ? _camera.zoom(1.15) : _camera.zoom(0.85);
}

void Viewer::timerEvent(QTimerEvent *){
  update();
}

//Events received from MainWindow
void Viewer::eventFromParent(QKeyEvent *e){

  if (e->key() == Qt::Key_Escape)
    close();

  else if (e->key() == Qt::Key_Right)
    _vef->translate(QVector3D(1,0,0)*0.5);
  else if (e->key() == Qt::Key_Left)
    _vef->translate(QVector3D(-1,0,0)*0.5);
  else if (e->key() == Qt::Key_Up)
    _vef->translate(QVector3D(0,1,0)*0.5);
  else if (e->key() == Qt::Key_Down)
    _vef->translate(QVector3D(0,-1,0)*0.5);
  else if (e->key() == Qt::Key_P)
    _vef->translate(QVector3D(0,0,1)*0.5);
  else if (e->key() == Qt::Key_M)
    _vef->translate(QVector3D(0,0,-1)*0.5);
  else if (e->key() == Qt::Key_A)
    _camera.zoom(0.95);
  else if (e->key() == Qt::Key_E)
    _camera.zoom(1.05);
  else if (e->key() == Qt::Key_Z)
    _camera.rotateLatitude(1);
  else if (e->key() == Qt::Key_S)
    _camera.rotateLatitude(-1);
  else if (e->key() == Qt::Key_Q)
    _camera.rotateLongitude(1);
  else if (e->key() == Qt::Key_D)
    _camera.rotateLongitude(-1);
  else
    QWidget::keyPressEvent(e);

  update();
}
