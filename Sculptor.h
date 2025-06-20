#ifndef SCULPTOR_H
#define SCULPTOR_H

#include "voxel.h"

class Sculptor {
private:
  Voxel ***v; // 3D matrix
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing color
public:
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();
  void setColor(float r, float g, float b, float alpha);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void putSphere(int xcenter, int ycenter, int zcenter, int radius); // cria uma esfera
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius); // apaga uma esfera
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz); // cria um elipsoide
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz); // apaga um elipsoide
  void writeOFF(const char* filename); 
};

#endif 