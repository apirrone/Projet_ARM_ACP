//3DViewer.hpp

#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLShaderProgram>

#include "VoxelGrid.hpp"

class Viewer : public QOpenGLWidget
{
  Q_OBJECT
  
public:
  explicit Viewer(VoxelGrid& grid, QWidget *parent = 0);
  ~Viewer();

  void rotateAroundAxis(float angle, QVector3D axis);
  void rotateAroundTarget(float angle, QVector3D axis);
  void translateCamera(QVector3D direction);
  
protected:
     void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

  void timerEvent(QTimerEvent *);
  void mouseMoveEvent(QMouseEvent *e);

private:
  VoxelGrid& _voxelGrid;
  QOpenGLShaderProgram * _shader;
  QMatrix4x4 _projectionMat;
  QMatrix4x4 _viewMat;
  QOpenGLVertexArrayObject _object;
  QOpenGLBuffer _vertexBufferId;
  QOpenGLBuffer* _faceBuffer;
  std::vector<VEF::Vertex> _vertices;
  std::vector<unsigned int> _faces;

  QVector3D _position;
  QVector3D _target;

  QVector2D prevPos;
  float angularSpeed;
  QVector3D rotationAxis;

  QBasicTimer timer;
};

#endif // VIEWER_HPP
