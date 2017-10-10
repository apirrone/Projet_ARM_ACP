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
// #include "utils.hpp"

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
  cerr << "USAGE : " << programName <<" <file.ext>" << endl;
}

int main(int argc, char *argv[]) {
  
  if(argc != 2){
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  
  QFileInfo fi(argv[1]);
  std::string extension = fi.suffix().toStdString();
  
  VEF* file = new VEF();
  
  if(extension.compare("obj")  == 0 || extension.compare("OBJ") == 0){
    cout << "coucouOBJ" << endl;
    file->loadFromObj(argv[1]);
  }
  else if(extension.compare("pgm3d") == 0){
    cout << "coucouPGM" << endl;
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
  
  //   //TEST OBJ
  // #ifdef OBJ

  // VEF* testObj = new VEF();
  // testObj->loadFromObj(argv[1]);
  // QApplication app(argc, argv);
  
  // MainWindow window(*testObj);
  // window.resize(1300,1300);
  // window.show();
  
  // cout << "FIN" << endl;
  
  // return app.exec();

  // #endif //OBJ
  // //TEST OBJ

  // #ifndef OBJ
  //   PGM3D_Holder test = PGM3D_Holder(argv[1]);
  
  //   int w = test.getWidth();
  //   int h = test.getHeight();
  //   int d = test.getDepth();
  
  //   const unsigned char * data = test.getData();
  
  //   VoxelGrid * grid = new VoxelGrid(h,w,d,data);
  //   cout << "DEBUT" << endl;
  
  QApplication app(argc, argv);
  
  MainWindow window(*file);
  window.resize(1300,1300);
  window.show();
  
  cout << "FIN" << endl;
  
  return app.exec();
  // #endif
}
