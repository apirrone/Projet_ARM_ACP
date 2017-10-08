#include "Camera.hpp"


Camera::Camera(){
}

Camera::Camera(QVector3D position, QVector3D target, int viewPortWidth, int viewPortHeight){
  initCamera(position, target, viewPortWidth, viewPortHeight);
}

Camera::~Camera(){}

void Camera::initCamera(QVector3D position, QVector3D target, int viewPortWidth, int viewPortHeight){

  _position = position;

  _target = target;

  _projectionMat.setToIdentity();
  _projectionMat.perspective(45.0f, viewPortWidth / float(viewPortHeight), 0.1f, 1000.0f);

  _viewMat.setToIdentity();
  _viewMat.lookAt(_position, _target, QVector3D(0,1,0));

}

void Camera::updateCamera(){
  //_viewMat.setToIdentity();
  //_viewMat.lookAt(_position, _target, QVector3D(0,1,0));
}

void Camera::updateProjectionMatrix(int width, int height){

  _projectionMat.setToIdentity();
  _projectionMat.perspective(45.0f, width / float(height), 0.1f, 1000.0f);

}

void Camera::setPosition(QVector3D position){
  _position = position;
  updateCamera();
}

void Camera::setTarget(QVector3D target){
  _target = target;
  updateCamera();
}

QMatrix4x4 Camera::getProjectionMatrix(){
  return _projectionMat;
}

QMatrix4x4 Camera::getViewMatrix(){
  updateCamera();
  return _viewMat;
}

void Camera::translateCamera(QVector3D direction){

  _position += direction;

  // std::cout << "_position.x() : " << _position.x() << " _position.y() : " << _position.y() << " _position.z() : " << _position.z()  << std::endl;

  _viewMat.setToIdentity();
  _viewMat.translate(direction);

  _viewMat.lookAt(_position, _target, QVector3D(0,1,0));
}

void Camera::rotateAroundTarget(float angle, QVector3D axis)
{
  /*_viewMat.setToIdentity();

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
*/
  _viewMat.translate(_target);
  _viewMat.rotate(-angle, axis);
  _viewMat.translate(-_target);
  //updateCamera();
}

void Camera::zoom(int orientation){
  _viewMat.translate(orientation*.1*(_viewMat*_target));
}
