#ifndef 3DVIEWER_HPP
#define 3DVIEWER_HPP

#include <QGLWidget>

class 3DViewer : public QGLWidget
{
  Q_OBJECT
public:
  explicit 3DViewer(QWidget *parent = 0);
  ~3DViewer();

protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

private:
  void draw();
};

#endif // 3DVIEWER_HPP
