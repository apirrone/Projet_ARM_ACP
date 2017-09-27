//SACViewer.hpp

#ifndef HAHALOLJOUJ
#define HAHALOLJOUJ

#include <QGLWidget>

class SACViewer : public QGLWidget
{
public:
  explicit SACViewer(QWidget *parent = 0);
  ~SACViewer();
  
protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

  QSize minimumSizeHint() const;
  QSize sizeHint() const;

private:
  void draw();
};

#endif // 3DVIEWERSAC_HPP
