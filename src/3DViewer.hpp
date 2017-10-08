//3DViewer.hpp

#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLShaderProgram>

#include "VoxelGrid.hpp"
#include "Camera.hpp"

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

private:
  VoxelGrid& _voxelGrid;
  QOpenGLShaderProgram * _shader;
  
  QOpenGLVertexArrayObject _object;
  QOpenGLBuffer _vertexBufferId;
  QOpenGLBuffer* _faceBuffer;
  
  std::vector<VEF::Vertex> _vertices;
  std::vector<unsigned int> _faces;

  QVector2D prevPos;
  float angularSpeed;
  QVector3D rotationAxis;
  
  Camera camera;
  
  QBasicTimer timer;
};

#endif // VIEWER_HPP
