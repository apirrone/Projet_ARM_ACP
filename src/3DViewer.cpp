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


  // _position = QVector3D(-33., -32., -148);
  _position = QVector3D(-32., -32., -143);
  unsigned int w = _voxelGrid.getW();
  unsigned int h = _voxelGrid.getH();
  unsigned int d = _voxelGrid.getD();
  _target = QVector3D(w/2., h/2., d/2.);
  
  // _position = QVector3D(0., 0., 0.);
  prevPos = QVector2D(0, 0);
  timer.start(0, this);
  // this.startTimer();
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

  _projectionMat.setToIdentity();
  _projectionMat.perspective(45.0f, this->width() / float(this->height()), 0.1f, 1000.0f);

  _viewMat.setToIdentity();
  // _viewMat.translate(_position);
  _viewMat.lookAt(_position, _target, QVector3D(0,1,0));
  // _viewMat.inverted();
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

void Viewer::translateCamera(QVector3D direction){
  
  _position += direction;
  
  // std::cout << "_position.x() : " << _position.x() << " _position.y() : " << _position.y() << " _position.z() : " << _position.z()  << std::endl;

  _viewMat.setToIdentity();
  _viewMat.translate(direction);
  
  _viewMat.lookAt(_position, _target, QVector3D(0,1,0));  

  update();
}

void Viewer::rotateAroundTarget(float angle, QVector3D axis)
{
  _viewMat.setToIdentity();
  
  QVector3D dir = _target - _position;

  QMatrix4x4 tmp;
  tmp.setToIdentity();

  tmp.translate(_position.x() , _position.y(), _position.z());
  tmp.translate(QVector3D(dir.x(), dir.y(), dir.z()));
  tmp.rotate(-angle, QVector3D(axis.x(), axis.y(), axis.z()));
  tmp.translate(QVector3D(-dir.x(), -dir.y(), -dir.z()));

  _position.setX(tmp.column(3).x());
  _position.setY(tmp.column(3).y());
  _position.setZ(tmp.column(3).z());
  
  _viewMat.lookAt(_position, _target, QVector3D(0,1,0));
  
  update();  
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
    rotateAroundTarget(angularSpeed, rotationAxis);
  }
}
