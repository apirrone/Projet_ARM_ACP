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

vector<string> ssplit(const string &s, char delim) {

  stringstream ss(s);
  string item;
  vector<string> tokens;

  while (getline(ss, item, delim))
    tokens.push_back(item);

  return tokens;

}

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
      file->loadFromObj(argv[1]);
      file->exportToObj("TestExport.obj");
    }
    else if(extension.compare("pgm3d") == 0){
      PGM3D_Holder test = PGM3D_Holder(argv[1]);

      int w = test.getWidth();
      int h = test.getHeight();
      int d = test.getDepth();

      const unsigned char * data = test.getData();

      file = new VoxelGrid(h,w,d,data);
    }
    else{
      cerr << "File extension : ." << extension <<" is not supported" << endl;
      return 0;
    }

    QApplication app(argc, argv);

    MainWindow window(*file);

    // TODO remove, duplicated
    window.resize(1300,1300);
    window.show();

    return app.exec();
  }
  // open without any file loaded
  else if (argc == 1) {
    QApplication app(argc, argv);
    MainWindow window(NULL);

    window.resize(1300,1300);
    window.show();

    return app.exec();
  }
  else {
    usage(argv[0]);
    return EXIT_FAILURE;
  }

}
