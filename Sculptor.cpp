#include "Sculptor.h"
#include <iostream>


void Sculptor::Sculptor(int _nx, int _ny, int _nz){

    this->nx = _nx;
    this->ny = _ny;
    this->nz = _nz;
    this->r = 0.0; // Red color component
    this->g = 0.0; // Green color component
    this->b = 0.0; // Blue color component

    // alocaçao dinamica da memoria para a matriz 3D de voxels
    v = new voxel **[_nx];
    for(int i = 0 ; i <_nx, i++){
        v[i] = new voxel *[_ny];
        for(int j = 0; j < _ny; j++){
            v[i][j] = new voxel[_nz];
            for(int k = 0; k < _nz; k++){
                this ->v[i][j][k].r = 0.0;
                this ->v[i][j][k].g = 0.0;
                this ->v[i][j][k].b = 0.0;
                this ->v[i][j][k].a = 0.0;
                this ->v[i][j][k].show = false; 
            }
        }
    }
}
// desalocando a memória alocada 
void Sculptor::~Sculptor(){
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            delete [] v[i][j]; // Libera a memória alocada para cada linha
        }
        delete [] v[i]; // Libera a memória alocada para cada coluna
    }
    delete [] v; // Libera a memória alocada para a matriz 3D de voxels
}

// define a  cor do voxel
void Sculptor::setColor(float r, float g, float b, float alpha){
    this -> r = r; 
    this -> g = g;
    this -> b = b;
    this -> a = alpha; 
}
 // cria um voxel nas posições x, y, z com as cores definidas no setColor
 void Sculptor::putVoxel(int x, int y, int z){
    this -> v[x][y][z].show = true;
    this -> v[x][y][z].r = r-> r;
    this -> v[x][y][z].g = g-> g;
    this -> v[x][y][z].b = b-> b;
    this -> v[x][y][z].a = a-> a;

}
void Sculptor::cutVoxel(int x, int y, int z){  
    this -> v[x][y][z].show = false; // Desativa o voxel
}
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    x0 = (x0 < 0) ? 0 : x0; // Garante que x0 não seja menor que 0
    x1 = (x1 > this -> nx) ? this -> nx - 1 : x1; // Garante que x1 não exceda o tamanho da matriz
    y0 = (y0 < 0) ? 0 : y0; // Garante que y0 não seja menor que 0
    y1 = (y1 > this -> ny) ? this -> ny - 1 : y1; // Garante que y1 não exceda o tamanho da matriz
    z0 = (z0 < 0) ? 0 : z0; // Garante que z0 não seja menor que 0
    z1 = (z1 > this -> nz) ? this -> nz - 1 : z1; // Garante que z1 não exceda o tamanho da matriz
    for(int i = x0; i < x1; i++){

        for(int j = y0; j < y1; j++){

            for(int k = z0; k < z1; k++){

                this -> putVoxel(i, j, k); // Chama a função putVoxel para cada voxel dentro do box
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
x0 = (x0 < 0) ? 0 : x0; // Garante que x0 não seja menor que 0
    x1 = (x1 > this -> nx) ? this -> nx - 1 : x1; // Garante que x1 não exceda o tamanho da matriz
    y0 = (y0 < 0) ? 0 : y0; // Garante que y0 não seja menor que 0
    y1 = (y1 > this -> ny) ? this -> ny - 1 : y1; // Garante que y1 não exceda o tamanho da matriz
    z0 = (z0 < 0) ? 0 : z0; // Garante que z0 não seja menor que 0
    z1 = (z1 > this -> nz) ? this -> nz - 1 : z1; // Garante que z1 não exceda o tamanho da matriz
    for(int i = x0; i < x1; i++){

        for(int j = y0; j < y1; j++){

            for(int k = z0; k < z1; k++){

                this -> cutBox(i, j, k);  // Chama a função cutVoxel para cada voxel dentro do box
            }
        }
    }

}
void  Sculptor:: putSphere(int xcenter, int ycenter, int zcenter, int radius){

    putEllipsoid(xcenter, ycenter, zcenter, radius, radius, radius);

}
void Sculptor:: cutSphere(int xcenter, int ycenter, int zcenter, int radius){

    cutEllipsoid(xcenter, ycenter, zcenter, radius, radius, radius);

}
void Sculptor:: putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int x0,x1, y0, y1, z0, z1;
    x0 = (xcenter - rx < 0) ? 0 : xcenter - rx; // Garante que x0 não seja menor que 0
    x1 = (xcenter + rx >= this->nx) ? this->nx - 1 : xcenter + rx; // Garante que x1 não exceda o tamanho da matriz
    y0 = (ycenter - ry < 0) ? 0 : ycenter - ry; // Garante que y0 não seja menor que 0
    y1 = (ycenter + ry >= this->ny) ? this->ny - 1 : ycenter + ry; // Garante que y1 não exceda o tamanho da matriz
    z0 = (zcenter - rz < 0) ? 0 : zcenter - rz; // Garante que z0 não seja menor que 0
    z1 = (zcenter + rz >= this->nz) ? this->nz - 1 : zcenter + rz; // Garante que z1 não exceda o tamanho da matriz

    for(int i =x0; i <x1; i++){
        for(int j = y0; j< y1; j++){
            for(int k = z0; k <z1; k++){

                if(isInsideEllipsoid(i, j, k, xcenter, ycenter, zcenter, rx, ry, rz)){
                    this -> putVoxel(i, j, k); // Chama a função putVoxel para cada voxel dentro do elipsoide
                }
            }
        }
    }
}
void Sculptor:: cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
        int x0,x1, y0, y1, z0, z1;
    x0 = (xcenter - rx < 0) ? 0 : xcenter - rx; // Garante que x0 não seja menor que 0

    x1 = (xcenter + rx >= this->nx) ? this->nx - 1 : xcenter + rx; // Garante que x1 não exceda o tamanho da matriz
    y0 = (ycenter - ry < 0) ? 0 : ycenter - ry; // Garante que y0 não seja menor que 0
    y1 = (ycenter + ry >= this->ny) ? this->ny - 1 : ycenter + ry; // Garante que y1 não exceda o tamanho da matriz
    z0 = (zcenter - rz < 0) ? 0 : zcenter - rz; // Garante que z0 não seja menor que 0
    z1 = (zcenter + rz >= this->nz) ? this->nz - 1 : zcenter + rz; // Garante que z1 não exceda o tamanho da matriz

    for(int i =x0; i <x1; i++){
        for(int j = y0; j< y1; j++){
            for(int k = z0; k <z1; k++){

                if(isInsideEllipsoid(i, j, k, xcenter, ycenter, zcenter, rx, ry, rz)){
                    this -> cutVoxel(i, j, k); // Chama a função cutVoxel para cada voxel dentro do elipsoide
                }
            }
        }
    }
}
void Sculptor:: writeOFF(const char* filename){
    
}
