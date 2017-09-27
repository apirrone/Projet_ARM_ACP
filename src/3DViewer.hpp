//3DViewer.hpp

#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>

class Viewer : public QGLWidget
{
  Q_OBJECT
  
public:
  explicit Viewer(QWidget *parent = 0);
  ~Viewer();
  
protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

private:
  void draw();
};

#endif // VIEWER_HPP
