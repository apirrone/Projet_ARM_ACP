#ifndef PGM3D_HOLDER_H
#define PGM3D_HOLDER_H

class pgm3D_Holder {

public:
  pgm3D_Holder(char* filePath);

private:
  // the image dimensions
  int width;
  int height;
  int depth;

  // the data stored in 1 byte long chunks
  unsigned char* data;
};

#endif // PGM3D_HOLDER_H
