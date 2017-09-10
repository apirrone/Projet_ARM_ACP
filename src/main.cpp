#include <cstdlib>
#include <iostream>
#include <fstream>
#include "PGM3D_Holder.hpp"

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
  
  return EXIT_SUCCESS;
}
