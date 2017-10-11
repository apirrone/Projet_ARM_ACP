//3DViewer.hpp

#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLShaderProgram>

#include "VoxelGrid.hpp"
#include "VEF.hpp"
#include "SatelliteCamera.hpp"
#include "Trackball.hpp"

class Viewer : public QOpenGLWidget
{
  Q_OBJECT

public:
  explicit Viewer(QWidget *parent = 0);
  explicit Viewer(VEF& grid, QWidget *parent = 0);
  ~Viewer();

  void setVEF(VEF * vef);

  void eventFromParent(QKeyEvent *e);
protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

  void timerEvent(QTimerEvent *);
  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  
private:
  VEF * _vef;//TODO Semble poser problème, check cast vers VoxelGrid dans le constructeur
  QOpenGLShaderProgram * _shader;

  QOpenGLVertexArrayObject _object;
  QOpenGLBuffer _vertexBufferId;
  QOpenGLBuffer* _faceBuffer;

  std::vector<VEF::Vertex> _vertices;
  std::vector<unsigned int> _faces;

  QVector2D _prevPos;
  float _angularSpeed;
  QVector3D _rotationAxis;

  SatelliteCamera _camera;

  QBasicTimer _timer;

  //Trackball _trackball;
};

#endif // VIEWER_HPP
