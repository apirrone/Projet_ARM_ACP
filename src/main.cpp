// main.cpp
#include <QApplication>
#include <QDesktopWidget>

#include "MainWindow.hpp"


#include <cstdlib>
#include <iostream>
#include <fstream>
#include "PGM3D_Holder.hpp"
#include "VoxelGrid.hpp"

// #define DEBUG
#define OBJ

using namespace std;

void usage(char* programName){
  cerr << "USAGE : " << programName <<" <file.pgm3d>" << endl;
}

int main(int argc, char *argv[]) {
  
  if(argc != 2){
    usage(argv[0]);
    return EXIT_FAILURE;
  }


  //TEST OBJ
#ifdef OBJ

  VEF* testObj = new VEF();
  testObj->loadFromObj(argv[1]);
  QApplication app(argc, argv);
  
  MainWindow window(*testObj);
  window.resize(1300,1300);
  window.show();
  
  cout << "FIN" << endl;
  
  return app.exec();

#endif //OBJ
  //TEST OBJ

#ifndef OBJ
  PGM3D_Holder test = PGM3D_Holder(argv[1]);
  
  int w = test.getWidth();
  int h = test.getHeight();
  int d = test.getDepth();
  
  const unsigned char * data = test.getData();
  
  VoxelGrid * grid = new VoxelGrid(h,w,d,data);
  cout << "DEBUT" << endl;
  
  QApplication app(argc, argv);
  
  MainWindow window(*grid);
  window.resize(1300,1300);
  window.show();
  
  cout << "FIN" << endl;
  
  return app.exec();
  #endif
}
