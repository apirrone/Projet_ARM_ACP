// MainWindow.cpp

#include <QtWidgets>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "3DViewer.hpp"
#include <iostream>

MainWindow::MainWindow(VoxelGrid& voxels, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
  // viewer(parent)
{
  ui->setupUi(this);

  viewer = new Viewer(voxels, this);
  this->setCentralWidget(viewer);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Escape)
    close();
  else if (e->key() == Qt::Key_Right)
    viewer->translateCamera(QVector3D(-1, 0, 0));
  else if (e->key() == Qt::Key_Left)
    viewer->translateCamera(QVector3D(1, 0, 0));
  else if (e->key() == Qt::Key_Up)
    viewer->translateCamera(QVector3D(0, -1, 0));
  else if (e->key() == Qt::Key_Down)
    viewer->translateCamera(QVector3D(0, 1, 0));
  else if (e->key() == Qt::Key_P)
    viewer->translateCamera(QVector3D(0, 0, 1));
  else if (e->key() == Qt::Key_L)
    viewer->translateCamera(QVector3D(0, 0, -1));
  else if (e->key() == Qt::Key_A)
    viewer->rotateAroundTarget(2, QVector3D(0, 1, 0));
  else if (e->key() == Qt::Key_E)
    viewer->rotateAroundTarget(-2, QVector3D(0, 1, 0));
  else 
    QWidget::keyPressEvent(e);
}


