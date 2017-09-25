// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>

#include "3DViewer.hpp"

3DViewer::3DViewer(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
}

3DViewer::~3DViewer()
{
}

QSize 3DViewer::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize 3DViewer::sizeHint() const
{
    return QSize(400, 400);
}

void 3DViewer::initializeGL()
{
}

void 3DViewer::paintGL()
{
}

void 3DViewer::resizeGL(int width, int height)
{

}

void 3DViewer::draw()
{

}
