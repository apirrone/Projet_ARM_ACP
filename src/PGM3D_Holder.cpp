#include "PGM3D_Holder.h"
#include <fstream>
#include <string>
#include <iostream>

pgm3D_Holder::pgm3D_Holder(char* filePath) {

  string line;
  ifstream fileToRead(filePath);

  if (fileToRead.is_open()) {
    while (getline(fileToRead, line)) {
      // store the relevant data
    }
    fileToRead.close();
  }
  else {
    // file could not be opened
    std::cerr << "The file : " << filePath <<" could not be opened" << std::endl;
    return;
  }
}
