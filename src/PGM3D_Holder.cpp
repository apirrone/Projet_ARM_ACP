#include <fstream>
#include <iostream>
#include <string.h>
#include <regex>
#include "PGM3D_Holder.hpp"

using namespace std;

PGM3D_Holder::PGM3D_Holder(char* filePath) {

  string line;
  ifstream fileToRead(filePath);

  if (fileToRead.is_open()) {
    // First, load the header
    getline(fileToRead, line);
    const auto rtline = regex_replace( line, regex( "\\s+$" ), "" ) ;
    if(rtline.compare("PGM3D") != 0){
      cerr << "Incorrect Header" << endl;
      fileToRead.close();
      return;
    }

    //parsing size line
    getline(fileToRead, line);


    char* temp;
    char* line_char = const_cast<char*>(line.c_str());

    temp = strtok(line_char, " ");

    char* res[3];

    int i = 0;
    while (temp != NULL){
      res[i++] = temp;
      temp = strtok(NULL, " ");
    }

    if(i != 3){
      cerr << "Incorrect Header" << endl;
      fileToRead.close();
      return;
    }


    _width = atoi(res[0]);
    _height = atoi(res[1]);
    _depth = atoi(res[2]);

    int size = _width*_height*_depth;

    //parsing max value line
    getline(fileToRead, line);

    _maxValue = stoi(line);

    _data = new unsigned char[size];

    // Then load the data in _data
    i = 0;
    while(getline(fileToRead, line)){
      size_t prev = 0, pos, end = min(line.find_first_of("#", 0), line.size());
      while(prev < end){
	pos = min(line.find_first_not_of("0123456789-", prev), end);
	if(i<size){
	  int val = stoi(line.substr(prev, pos-prev));
	  if(val >= 0 && val <= _maxValue)
	    _data[i] = val;
	  else{
	    cerr << "Value (" << val << ") is not in range [O;" << _maxValue << "]" << endl;
	    fileToRead.close();
	    return;
	  }
	}
	else{
	  cerr << "Too many values." << endl;
	  fileToRead.close();
	  return;
	}
	prev = pos+1;
	i++;
      }
    }

    fileToRead.close();
  }
  else {
    // file could not be opened
    cerr << "The file : " << filePath <<" could not be opened" << endl;
    return;
  }

}

PGM3D_Holder::~PGM3D_Holder()
{
  delete[] _data;
}

int PGM3D_Holder::getWidth() const
{
  return _width;
}

int PGM3D_Holder::getHeight() const
{
  return _height;
}

int PGM3D_Holder::getDepth() const
{
  return _depth;
}

int PGM3D_Holder::getMaxValue() const
{
  return _maxValue;
}

const unsigned char* PGM3D_Holder::getData() const
{
  return _data;
}

unsigned char PGM3D_Holder::getValue(int x, int y, int z) const
{
  return _data[(x*_width+y)*_depth+z];
}
