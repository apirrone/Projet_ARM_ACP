// MainWindow.cpp

#include <QtWidgets>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "3DViewer.hpp"
#include "PGM3D_Holder.hpp"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  viewer = new Viewer(this);


  createActions();
  createMenu();
  setWindowTitle(tr("Visiobrain"));

  VEF * v = new VEF();
  v->loadFromObj("../data/hand.OBJ");
  viewer->setVEF(*v);

  this->setCentralWidget(viewer);
}

MainWindow::MainWindow(VEF& voxels, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  viewer = new Viewer(voxels, this);
  this->setCentralWidget(viewer);

  createActions();
  createMenu();
  setWindowTitle(tr("Visiobrain"));


  
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e){

  viewer->eventFromParent(e);
}

void MainWindow::createActions() {

  openAction = new QAction(tr("&Open"), this);
  openAction->setStatusTip(tr("Open a file from your computer"));
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

  exportAsAction = new QAction(tr("&Export as OBJ"), this);
  exportAsAction->setStatusTip(tr("Export this model as OBJ file"));
  connect(exportAsAction, SIGNAL(triggered()), this, SLOT(exportAs()));

  exitAction = new QAction(tr("&Exit"), this);
  exitAction->setStatusTip(tr("Exit the program"));
  connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));
}

void MainWindow::createMenu() {

  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAction);
  fileMenu->addAction(exportAsAction);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);
}

void MainWindow::open() {

  std::cout << "Open called" << '\n';
  // QFileDialog fd(this);
  // fd.setOption(QFileDialog::DontUseNativeDialog, true);
  //fd.exec();
  
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"../data", tr("3D files (*.obj *pgm3d)"), Q_NULLPTR, QFileDialog::Options(QFileDialog::DontUseNativeDialog));
  ///*
  std::cout << "opened : " << fileName.toStdString() << '\n';
  QFileInfo fileInfo(fileName);
  QString fileExtension = fileInfo.suffix();
  std::cout << "file extension : " << fileExtension.toStdString() << '\n';

  if(fileExtension.toStdString() == "obj" || fileExtension.toStdString() == "OBJ")//TODO tolower
    {
      VEF * v = new VEF();
      v->loadFromObj(fileName.toStdString());
      viewer->setVEF(*v);
    }
  else if(fileExtension.toStdString() == "pgm3d" || fileExtension.toStdString() == "PGM3D")
    {
      PGM3D_Holder test = PGM3D_Holder(fileName.toStdString().c_str());

      int w = test.getWidth();
      int h = test.getHeight();
      int d = test.getDepth();

      const unsigned char * data = test.getData();

      VEF * v = new VoxelGrid(h,w,d,data);
      viewer->setVEF(*v);
      
    }
  //*/
}

void MainWindow::exportAs() {

  std::cout << "export As" << '\n';
}

void MainWindow::exit() {

  this->close();
}
