#ifndef PGM3D_HOLDER_H
#define PGM3D_HOLDER_H

class PGM3D_Holder {

 public:
  PGM3D_Holder(char* filePath);

 private:
  // the image dimensions
  int _width;
  int _height;
  int _depth;
  
  // the data stored in 1 byte long chunks
  unsigned char* _data;
};

#endif // PGM3D_HOLDER_H
