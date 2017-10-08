#include "Trackball.hpp"
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Trackball::track(const QVector2D &point2D){
  
  if(_isTracking){

    QVector3D newPoint3D;
    bool newPointOk = mapToSphere(point2D, newPoint3D);

    if (_lastPointOk && newPointOk) {

      QVector3D axis = QVector3D::crossProduct(_lastPoint3D, newPoint3D);
      float cos_angle = QVector3D::dotProduct(_lastPoint3D, newPoint3D);
    
      if ( std::abs(cos_angle) < 1.0 && axis.length()>0) {
      
	float angle = 40. * std::acos(cos_angle);
	_camera->rotateAroundTarget(angle, axis.normalized());
      }
    }
  
    _lastPoint3D = newPoint3D;
    _lastPointOk = newPointOk;
  }  
}

bool Trackball::mapToSphere(const QVector2D &p2, QVector3D &v3)
{

  if ((p2.x() >= 0) && (p2.x() <= int(_camera->getVpWidth())) &&
      (p2.y() >= 0) && (p2.y() <= int(_camera->getVpHeight())) )
    {
      double x  = (double)(p2.x() - 0.5*_camera->getVpWidth())  / (double)_camera->getVpWidth();
      double y  = (double)(0.5*_camera->getVpHeight() - p2.y()) / (double)_camera->getVpHeight();
      double sinx         = std::sin(M_PI * x * 0.5);
      double siny         = std::sin(M_PI * y * 0.5);
      double sinx2siny2   = sinx * sinx + siny * siny;

      v3 = QVector3D(sinx, siny, (sinx2siny2 < 1.0 ? sqrt(1.0 - sinx2siny2) : 0.0));
      
      // v3 << sinx,
      // 	siny,
      // 	(sinx2siny2 < 1.0 ? sqrt(1.0 - sinx2siny2) : 0.0);
      
      return true;
    }
  else
    return false;
}

void Trackball::setCamera(Camera* camera){
  _camera = camera;
}
