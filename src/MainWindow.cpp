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

void MainWindow::keyPressEvent(QKeyEvent *e){

  viewer->eventFromParent(e);
  
  // std::cout << "coucou"<< std::endl;
  // if (e->key() == Qt::Key_Escape)
  // 		 close();
  // 	       else if (e->key() == Qt::Key_Right)
  // 		 camera.translateCamera(QVector3D(-1, 0, 0));
  // 	       else if (e->key() == Qt::Key_Left)
  // 		 camera.translateCamera(QVector3D(1, 0, 0));
  // 	       else if (e->key() == Qt::Key_Up)
  // 		 camera.translateCamera(QVector3D(0, -1, 0));
  // 	       else if (e->key() == Qt::Key_Down)
  // 		 camera.translateCamera(QVector3D(0, 1, 0));
  // 	       else if (e->key() == Qt::Key_P)
  // 		 camera.translateCamera(QVector3D(0, 0, 1));
  // 	       else if (e->key() == Qt::Key_L)
  // 		 camera.translateCamera(QVector3D(0, 0, -1));
  // 	       else if (e->key() == Qt::Key_A)
  // 		 camera.rotateAroundTarget(2, QVector3D(0, 1, 0));
  // 	       else if (e->key() == Qt::Key_E)
  // 		 camera.rotateAroundTarget(-2, QVector3D(0, 1, 0));
  // 	       else 
  // 		 QWidget::keyPressEvent(e);
  // update();
}
