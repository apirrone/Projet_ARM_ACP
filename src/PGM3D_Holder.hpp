#ifndef PGM3D_HOLDER_HPP
#define PGM3D_HOLDER_HPP

class PGM3D_Holder {

public:
  PGM3D_Holder(char* filePath);
  ~PGM3D_Holder();

private:
  // the image dimensions
  int _width;
  int _height;
  int _depth;
  int _maxValue;
  
  // the data stored in 1 byte long chunks
  unsigned char* _data;
};

#endif // PGM3D_HOLDER_HPP
