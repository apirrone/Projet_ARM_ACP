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

  void rotateAroundTarget(float angle, QVector3D axis);
  
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
  QOpenGLVertexArrayObject _object;
  QOpenGLBuffer _vertexBufferId;
  QOpenGLBuffer* _faceBuffer;
  std::vector<VEF::Vertex> _vertices;
  std::vector<unsigned int> _faces;

};

#endif // VIEWER_HPP
