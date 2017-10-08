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

using namespace std;

void usage(char* programName){
  cerr << "USAGE : " << programName <<" <file.pgm3d>" << endl;
}

int main(int argc, char *argv[]) {

  
  if(argc != 2){
    usage(argv[0]);
    return EXIT_FAILURE;
  }

  PGM3D_Holder test = PGM3D_Holder(argv[1]);
  
  int w = test.getWidth();
  int h = test.getHeight();
  int d = test.getDepth();
  
  const unsigned char * data = test.getData();
  
#ifdef DEBUG
  
  cout << "Test : \n\t - w : " << w << endl
       << "\t - h : " << h << endl
       << "\t - d : " << d << endl
       << "\t - max : " << test.getMaxValue() << endl;
  
  for(int i = 0; i < w*h*d; ++i)
    cout << "\t - data[" << i << "] = " << (int)data[i] << endl;
  
#endif

  VoxelGrid * grid = new VoxelGrid(h,w,d,data);
  cout << "DEBUT" << endl;
  
  QApplication app(argc, argv);
  
  MainWindow window(*grid);
  window.resize(800,600);
  window.show();
  
  cout << "FIN" << endl;
  
  return app.exec();
}
