// MainWindow.cpp

#include <QtWidgets>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "3DViewer.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
  // viewer(parent)
{
  ui->setupUi(this);

  viewer = new Viewer(this);
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
  else
    QWidget::keyPressEvent(e);
}
