//3DViewer.hpp

#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>
#include "Voxel.hpp"
class Viewer : public QGLWidget
{
  Q_OBJECT
  
public:
  explicit Viewer(std::vector<Voxel>* voxels, QWidget *parent = 0);
  ~Viewer();
  
protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

private:
  void draw();
  std::vector<Voxel>* _voxels;
};

#endif // VIEWER_HPP
