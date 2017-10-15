// MainWindow.cpp

#include <QtWidgets>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "PGM3D_Holder.hpp"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  _ui(new Ui::MainWindow)
{
  _ui->setupUi(this);

  _viewer = new Viewer(this);


  createActions();
  createMenu();
  setWindowTitle(tr("Visiobrain"));

  this->setCentralWidget(_viewer);
}

MainWindow::MainWindow(VEF& voxels, QWidget *parent) :
  QMainWindow(parent),
  _ui(new Ui::MainWindow)
{
  _ui->setupUi(this);

  _viewer = new Viewer(voxels, this);
  this->setCentralWidget(_viewer);

  createActions();
  createMenu();
  setWindowTitle(tr("Visiobrain"));
}

MainWindow::~MainWindow()
{
  delete _ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e){

  _viewer->eventFromParent(e);
}

void MainWindow::createActions() {

  _openAction = new QAction(tr("&Open"), this);
  _openAction->setStatusTip(tr("Open a file from your computer"));
  connect(_openAction, SIGNAL(triggered()), this, SLOT(open()));

  _exportAsObjAction = new QAction(tr("&Export as OBJ"), this);
  _exportAsObjAction->setStatusTip(tr("Export this model as OBJ file"));
  connect(_exportAsObjAction, SIGNAL(triggered()), this, SLOT(exportAsObj()));

  _exitAction = new QAction(tr("&Exit"), this);
  _exitAction->setStatusTip(tr("Exit the program"));
  connect(_exitAction, SIGNAL(triggered()), this, SLOT(exit()));
}

void MainWindow::createMenu() {

  _fileMenu = menuBar()->addMenu(tr("&File"));
  _fileMenu->addAction(_openAction);
  _fileMenu->addAction(_exportAsObjAction);
  _fileMenu->addSeparator();
  _fileMenu->addAction(_exitAction);
}

// Handles the opening of a 3D file
void MainWindow::open() {

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"../data", tr("3D files (*.obj *pgm3d)"), Q_NULLPTR, QFileDialog::Options(QFileDialog::DontUseNativeDialog));

  QFileInfo fileInfo(fileName);
  QString fileExtension = fileInfo.suffix();

  if(fileExtension.toStdString() == "obj" || fileExtension.toStdString() == "OBJ"){//TODO tolower
    VEF * v = new VEF();
    v->loadFromObj(fileName.toStdString());
    _viewer->setVEF(*v);
  }
  else if(fileExtension.toStdString() == "pgm3d" || fileExtension.toStdString() == "PGM3D"){
    PGM3D_Holder test = PGM3D_Holder(fileName.toStdString().c_str());

    int w = test.getWidth();
    int h = test.getHeight();
    int d = test.getDepth();

    const unsigned char * data = test.getData();

    VEF * v = new VoxelGrid(h,w,d,data);
    _viewer->setVEF(*v);
  }
}

void MainWindow::exportAsObj() {

  QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save model as obj"), "../data",
        tr("3D model (*.obj)"));

  _viewer->getVEF()->exportToObj(fileName.toStdString());
}

void MainWindow::exit() {

  this->close();
}
