#include "3DViewer.hpp"

#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
/*
Viewer::Viewer(QWidget *parent)
  : QOpenGLWidget(parent)
{
  QSurfaceFormat format;
  format.setVersion(3, 3);

  this->setFormat(format);

  _prevPos = QVector2D(0, 0);
  _timer.start(0, this);
}
*/
Viewer::Viewer(VEF& grid, QWidget *parent)
  : QOpenGLWidget(parent),
    _vef(grid)
{
  QSurfaceFormat format;

  format.setVersion(3, 3);

  this->setFormat(format);

  _prevPos = QVector2D(0, 0);
  _timer.start(0, this);

  // unsigned int w = _vef.getW();
  // unsigned int h = _vef.getH();
  // unsigned int d = _vef.getD();
  // std::cout << "this->width() : " << this->width()  << std::endl;
  // _camera = Camera(QVector3D(-32., -32., -143), QVector3D(w/2., h/2., d/2.), this->width(), this->height());
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
  //f->glEnable(GL_CULL_FACE);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  f->glEnable(GL_BLEND);
  f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //shader init
  _shader = new QOpenGLShaderProgram();
  _shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "../data/shaders/simple.vert");
  _shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "../data/shaders/simple.frag");
  _shader->link();
  _shader->bind();

  unsigned int w = _vef.getW();
  unsigned int h = _vef.getH();
  unsigned int d = _vef.getD();

  std::cout << "w : " << w  << std::endl;
  std::cout << "h : " << h  << std::endl;
  std::cout << "d : " << d  << std::endl;

  //_camera.initCamera(300, 0, 0, QVector3D(-1.*w/2, 1.*h/2, d/2), this->width(), this->height(), 45.);
  _camera.initCamera(300, 0, 0, QVector3D(0, 0, 0), this->width(), this->height(), 45.);
  //_trackball.setCamera(&_camera);
}

void Viewer::paintGL(){

  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(0.2, 0.2, 0.2, 1.0);
  f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  _shader->bind();
  _shader->setUniformValue(_shader->uniformLocation("proj_mat"), _camera.projectionMatrix());
  _shader->setUniformValue(_shader->uniformLocation("view_mat"), _camera.viewMatrix());

  _vef.draw(_shader);
  _shader->release();
}

void Viewer::resizeGL(int width, int height){
  QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
  f->glViewport( 0, 0, (GLint)width, (GLint)height );
  _camera.setViewPort(width, height);
  //_camera.updateProjectionMatrix(width, height);
}

void Viewer::mousePressEvent(QMouseEvent *e){
  //  _trackball.start();
  //_trackball.track(_prevPos);
}

void Viewer::mouseReleaseEvent(QMouseEvent *e){
  //_trackball.stop();

}

void Viewer::mouseMoveEvent(QMouseEvent *e){
  //_trackball.track(QVector2D(e->localPos()));

  // QVector2D diff = QVector2D(e->localPos()) - _prevPos;
  // QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

  // qreal acc = diff.length() / 500.0;


  // _rotationAxis = (_rotationAxis * _angularSpeed + n * acc).normalized();

  // _angularSpeed += acc;

  _prevPos = QVector2D(e->localPos());
}

void Viewer::timerEvent(QTimerEvent *){
  // angularSpeed *= 0.97;

  // if (angularSpeed < 0.02) {
  //   angularSpeed = 0.0;
  // } else {
  //   _camera.rotateAroundTarget(angularSpeed, rotationAxis);
  //   updat();
  // }
  update();//TODO ne pas faire ca, update que quand il y a besoin
}

void Viewer::eventFromParent(QKeyEvent *e){

  if (e->key() == Qt::Key_Escape)
    close();
  /*
  else if (e->key() == Qt::Key_Right)
    //_camera.translateCamera(QVector3D(-1, 0, 0));
  else if (e->key() == Qt::Key_Left)
    //_camera.translateCamera(QVector3D(1, 0, 0));
  else if (e->key() == Qt::Key_Up)
    //_camera.translateCamera(QVector3D(0, -1, 0));
  else if (e->key() == Qt::Key_Down)
    //_camera.translateCamera(QVector3D(0, 1, 0));
  else if (e->key() == Qt::Key_P)
    //_camera.translateCamera(QVector3D(0, 0, 1));
  else if (e->key() == Qt::Key_L)
    //_camera.translateCamera(QVector3D(0, 0, -1));
    */
  else if (e->key() == Qt::Key_A){
    // _camera.rotateAroundTarget(2, QVector3D(0, 1, 0));
    _camera.zoom(0.95);
  }else if (e->key() == Qt::Key_E){
    //_camera.rotateAroundTarget(-2, QVector3D(0, 1, 0));
    _camera.zoom(1.05);
  }else if (e->key() == Qt::Key_Z){
    //_camera.zoom(1);
    _camera.rotateLatitude(1);
  }else if (e->key() == Qt::Key_S){
    //_camera.zoom(-1);
    _camera.rotateLatitude(-1);
  }else if (e->key() == Qt::Key_Q){
    _camera.rotateLongitude(1);
  }else if (e->key() == Qt::Key_D){
    _camera.rotateLongitude(-1);
  }
  else
    QWidget::keyPressEvent(e);

  update();
}
