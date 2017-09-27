// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>

#include "3DViewer.hpp"

SACViewer::SACViewer(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
}

SACViewer::~SACViewer()
{
}

QSize SACViewer::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize SACViewer::sizeHint() const
{
    return QSize(400, 400);
}

void SACViewer::initializeGL()
{
}

void SACViewer::paintGL()
{
}

void SACViewer::resizeGL(int width, int height)
{

}

void SACViewer::draw()
{

}
