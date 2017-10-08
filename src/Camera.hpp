//Camera.hpp


#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QtOpenGL>

class Camera
{

public:
  Camera();
  Camera(QVector3D Position, QVector3D target, int viewPortWidth, int viewPortHeight);
  ~Camera();

  void initCamera(QVector3D position, QVector3D target, int viewPortWidth, int viewPortHeight);
  void rotateAroundAxis(float angle, QVector3D axis);
  void rotateAroundTarget(float angle, QVector3D axis);
  void zoom(int orientation);
  void translateCamera(QVector3D direction);
  void updateCamera();
  void updateProjectionMatrix(int width, int height);
  void setPosition(QVector3D position);
  void setTarget(QVector3D target);
  QMatrix4x4 getProjectionMatrix();
  QMatrix4x4 getViewMatrix();


private:
  QMatrix4x4 _projectionMat;
  QMatrix4x4 _viewMat;

  QVector3D _position;
  QVector3D _target;

  QVector2D _prevPos;
  float _angularSpeed;
  QVector3D _rotationAxis;



};

#endif // CAMERA_HPP
