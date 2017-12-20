// main.cpp
#include <QApplication>
#include <QDesktopWidget>

#include "MainWindow.hpp"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "PGM3D_Holder.hpp"
#include "VoxelGrid.hpp"
#include <string.h>

// #define DEBUG
// #define OBJ

using namespace std;

void usage(char* programName){
  cerr << "USAGE : " << programName <<" [optionnal]<file.ext>" << endl;
}

int main(int argc, char *argv[]) {

  // open the file given as argument
  if (argc == 2) {
    QFileInfo fi(argv[1]);
    std::string extension = fi.suffix().toStdString();

    VEF* file = new VEF();

    if(extension.compare("obj")  == 0 || extension.compare("OBJ") == 0){
      //file->loadFromObj(argv[1]);
      file->loadHalfEdges(argv[1]);
    }
    else if(extension.compare("pgm3d") == 0){
      PGM3D_Holder holder = PGM3D_Holder(argv[1]);

      int w = holder.getWidth();
      int h = holder.getHeight();
      int d = holder.getDepth();

      const unsigned char * data = holder.getData();

      file = new VoxelGrid(h,w,d,data);
      file->loadSurfaceMesh();
    }
    else{
      cerr << "File extension : ." << extension <<" is not supported" << endl;
      return 0;
    }

    QApplication app(argc, argv);

    MainWindow window(*file);

    window.resize(1300,1300);
    window.show();

    return app.exec();
  }

  // open without any file loaded
  else if (argc == 1) {

    QApplication app(argc, argv);
    MainWindow window;

    window.resize(1300,1300);
    window.show();

    return app.exec();
  }
  else {

    usage(argv[0]);
    return EXIT_FAILURE;

  }

}
