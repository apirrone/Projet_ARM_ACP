// MainWindow.cpp

#include <QtWidgets>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "3DViewer.hpp"
#include <iostream>

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
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"../data", tr("3D files (*.obj *pgm3d)"));
  //ui->listWidget->addItems(fileNames);
  std::cout << "opened : " << fileName.toStdString() << '\n';
}

void MainWindow::exportAs() {

  std::cout << "export As" << '\n';
}

void MainWindow::exit() {

  this->close();
}
