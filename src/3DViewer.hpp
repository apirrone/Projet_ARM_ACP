//3DViewer.hpp

#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "VoxelGrid.hpp"

class Viewer : public QGLWidget
{
  Q_OBJECT
  
public:
  explicit Viewer(VoxelGrid& grid, QWidget *parent = 0);
  ~Viewer();
  
protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

private:
  VoxelGrid& _voxelGrid;
  QOpenGLShaderProgram * _shader;
  QMatrix4x4 _projectionMat;
  QMatrix4x4 _viewMat;
};

#endif // VIEWER_HPP
