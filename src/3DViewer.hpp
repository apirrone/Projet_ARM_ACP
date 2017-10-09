//3DViewer.hpp

#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLShaderProgram>

#include "VoxelGrid.hpp"
#include "SatelliteCamera.hpp"
#include "Trackball.hpp"

class Viewer : public QOpenGLWidget
{
  Q_OBJECT
  
public:
  explicit Viewer(VoxelGrid& grid, QWidget *parent = 0);
  ~Viewer();

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
  VoxelGrid& _voxelGrid;
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
