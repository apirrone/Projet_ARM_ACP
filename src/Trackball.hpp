#ifndef TRACKBALL_HPP
#define TRACKBALL_HPP

#include <QtOpenGL>
#include "Camera.hpp"

class Trackball
{

public:
  Trackball() : _camera(0){};

  void start(){_lastPointOk = false;_isTracking=true;}
  void stop(){_isTracking=false;}
  void track(const QVector2D &point2D);
  void setCamera(Camera* camera);

  
private:

  bool mapToSphere(const QVector2D &newPoint2D, QVector3D &v3);

  Camera* _camera;
  QVector3D _lastPoint3D;
  bool _lastPointOk;
  bool _isTracking;
};


#endif // TRACKBALL_HPP
