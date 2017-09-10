#include "PGM3D_Holder.h"
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

PGM3D_Holder::PGM3D_Holder(char* filePath) {

  string line;
  ifstream fileToRead(filePath);

  if (fileToRead.is_open()) {
    // First, load the header
    getline(fileToRead, line);
    
    if(line.compare("PGM3D") != 0){
      cerr << "Incorrect Header" << endl;
      return;
    }

    getline(fileToRead, line);
    
    char* temp;
    char* line_char = const_cast<char*>(line.c_str());
    
    temp = strtok(line_char, " ");

    char* res[3];
    
    int i = 0;
    while (temp != NULL) {
      res[i++] = temp;
      temp = strtok(NULL, " ");
    }

    if(i != 3){
      cerr << "Incorrect Header" << endl;
      return;
    }
    
    
    _width = atoi(res[0]);
    _height = atoi(res[1]);
    _depth = atoi(res[2]);

    
    getline(fileToRead, line);
    
    _maxValue = stoi(line);
    
    _data = new unsigned char(_width*_height*_depth);

    // Then load the data in _data
    i = 0;
    while (getline(fileToRead, line)) 
      _data[i] = stoi(line);
    
    
    fileToRead.close();
  }
  else {
    // file could not be opened
    cerr << "The file : " << filePath <<" could not be opened" << endl;
    return;
  }
  
}
