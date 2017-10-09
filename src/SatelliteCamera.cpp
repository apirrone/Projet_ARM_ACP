#include <iostream>
#include "SatelliteCamera.hpp"

SatelliteCamera::SatelliteCamera() : _near(0.1), _far(1000.) {}

SatelliteCamera::SatelliteCamera(float distToTarget, float longitude, float latitude, QVector3D target, int viewPortWidth, int viewPortHeight, float FOV)
  : _distToTarget(distToTarget), _longitude(longitude), _latitude(latitude), _target(target), _vpWidth(viewPortWidth), _vpHeight(viewPortHeight), _fov(FOV), _updateProjMat(true), _updateViewMat(true), _near(0.1f), _far(1000.0f) { }

SatelliteCamera::~SatelliteCamera() { }

void SatelliteCamera::initCamera(float distToTarget, float longitude, float latitude, QVector3D target, int viewPortWidth, int viewPortHeight, float FOV) {
  _distToTarget = distToTarget;
  _longitude = longitude;
  _latitude = latitude;
  _target = target;
  _vpWidth = viewPortWidth;
  _vpHeight = viewPortHeight;
  _fov = FOV;
  _updateViewMat = true;
  _updateProjMat = true;
}

void SatelliteCamera::rotateLongitude(float lon) {
  _longitude += lon;
  _updateViewMat = true;
}
void SatelliteCamera::rotateLatitude(float lat) {
  _latitude += lat;
  _updateViewMat = true;
}
void SatelliteCamera::zoom(float factor) {
  _distToTarget /= factor;
  _updateViewMat = true;
  //_viewMat.translate(QVector3D(0,0,1));
  //_updateViewMat = false;
}

void SatelliteCamera::setDistanceToTarget(float dist) {
  _distToTarget = dist;
  _updateViewMat = true;
}
void SatelliteCamera::setLongitude(float lon) {
  _longitude = lon;
  _updateViewMat = true;
}
void SatelliteCamera::setLatitude(float lat) {
  _latitude = lat;
  _updateViewMat = true;
}

void SatelliteCamera::setTarget(QVector3D target) {
  _target = target;
  _updateViewMat = true;
}

QMatrix4x4 SatelliteCamera::projectionMatrix() {
  if(!_updateProjMat)
    return _projectionMat;
  std::cout << "fov : " << _fov << " w : " << _vpWidth << " h : " << _vpHeight << " near : " << _near << " far : " << _far << std::endl;
  _projectionMat.setToIdentity();
  _projectionMat.perspective(_fov, _vpWidth/_vpHeight, _near, _far);
  _updateProjMat = false;
  return _projectionMat;
}
QMatrix4x4 SatelliteCamera::viewMatrix() {
  if(!_updateViewMat)
    return _viewMat;
  std::cout << "dist : " << _distToTarget << " lat : " << _latitude << " lon : " << _longitude << std::endl;
  _viewMat.setToIdentity();
  //_viewMat.lookAt(QVector3D(0.,0.,143), QVector3D(0,0,0), QVector3D(0.,1.,0.));
  _viewMat.lookAt(QVector3D(0.,0.,0.), QVector3D(0,0,-1), QVector3D(0.,1.,0.));
  _viewMat.translate(-_distToTarget * QVector3D(0,0,1));
  _viewMat.rotate(_latitude, QVector3D(1,0,0));
  _viewMat.rotate(_longitude, QVector3D(0,1,0));
  _viewMat.translate(_target);
  _updateViewMat = false;
  return _viewMat;
}

void SatelliteCamera::setViewPort(float width, float height) {
  _vpWidth = width;
  _vpHeight = height;
  _updateProjMat = true;
}
void SatelliteCamera::setFOV(float fov) {
  _fov = fov;
  _updateProjMat = true;
}  
