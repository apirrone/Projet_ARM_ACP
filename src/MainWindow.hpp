// MainWindow.hpp

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QSlider>

#include "3DViewer.hpp"
#include "VoxelGrid.hpp"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  // Q_OBJECT

public:
  explicit MainWindow(VoxelGrid& voxels, QWidget *parent = 0);
  ~MainWindow();

protected:
  void keyPressEvent(QKeyEvent *event);

private:
  Ui::MainWindow *ui;
  Viewer* viewer;
};

#endif // MAINWINDOW_HPP
