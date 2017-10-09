//SatelliteCamera.hpp


#ifndef SATELLITE_CAMERA_HPP
#define SATELLITE_CAMERA_HPP

#include <QtOpenGL>

class SatelliteCamera
{

public:
  SatelliteCamera();
  SatelliteCamera(float distToTarget, float longitude, float latitude, QVector3D target, int viewPortWidth, int viewPortHeight, float fov);
  ~SatelliteCamera();

  void initCamera(float distToTarget, float longitude, float latitude, QVector3D target, int viewPortWidth, int viewPortHeight, float fov);
  void rotateLongitude(float lon);
  void rotateLatitude(float lat);
  void zoom(float factor);
  void setDistanceToTarget(float dist);
  void setLongitude(float lon);
  void setLatitude(float lat);
  void setTarget(QVector3D target);
  QMatrix4x4 projectionMatrix();
  QMatrix4x4 viewMatrix();
  void setViewPort(float width, float height);
  void setFOV(float FOV);
  
private:
  bool _updateProjMat;
  QMatrix4x4 _projectionMat;
  bool _updateViewMat;
  QMatrix4x4 _viewMat;

  float _distToTarget, _longitude, _latitude;

  QVector3D _target;

  float _vpHeight, _vpWidth, _fov;
  float _near, _far;
};

#endif // SATELLITE_CAMERA_HPP
