#include "Sculptor.h"
#include <iostream>
#include <fstream>
#include <iomanip>


Sculptor::Sculptor(int _nx, int _ny, int _nz){

    this->nx = _nx;
    this->ny = _ny;
    this->nz = _nz;
    this->r = 0.0; // Red color component
    this->g = 0.0; // Green color component
    this->b = 0.0; // Blue color component

    // alocaçao dinamica da memoria para a matriz 3D de voxels
    v = new Voxel **[_nx];
    for(int i = 0 ; i <_nx; i++){
        v[i] = new Voxel *[_ny];
        for(int j = 0; j < _ny; j++){
            v[i][j] = new Voxel[_nz];
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
Sculptor::~Sculptor(){
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
    this -> v[x][y][z].r = this-> r;
    this -> v[x][y][z].g = this-> g;
    this -> v[x][y][z].b = this-> b;
    this -> v[x][y][z].a = this-> a;

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

                this -> cutVoxel(i, j, k);  // Chama a função cutVoxel para cada voxel dentro do box
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
                float dx = float(i - xcenter) / rx; // Normaliza a coordenada x
                float dy = float(j - ycenter) / ry; // Normaliza a coordenada y
                float dz = float(k - zcenter) / rz; // Normaliza a coordenada z
                if((dx * dx + dy * dy + dz * dz) <= 1.0){ // Verifica se o ponto está dentro do elipsoide
                    putVoxel(i, j, k); // Chama a função putVoxel para cada voxel dentro do elipsoide
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
                 float dx = float(i - xcenter) / rx; // Normaliza a coordenada x
                float dy = float(j - ycenter) / ry; // Normaliza a coordenada y
                float dz = float(k - zcenter) / rz; // Normaliza a coordenada z
                if((dx * dx + dy * dy + dz * dz) <= 1.0){ // Verifica se o ponto está dentro do elipsoide
                    cutVoxel(i, j, k); // Chama a função putVoxel para cada voxel dentro do elipsoide
                }
                }
            }
        }
    }

void Sculptor::writeOFF(const char* filename){
    int NVoxels = 0;
    int NVertices, NFaces;
    int vertexIndex = 0;

     std::ofstream fout;
     
    fout.open(filename);
    if (!fout.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo.\n";
        exit(1);
    }

    fout << "OFF\n";

    // Conta o número de voxels ativos
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].show){
                    NVoxels++;
                }
            }
        }
    }

    NVertices = NVoxels * 8;
    NFaces = NVoxels * 6;

    fout << NVertices << " " << NFaces << " 0\n";

    // Escreve os vértices
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].show){
                    fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << "\n"
                         << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << "\n"
                         << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << "\n"
                         << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << "\n"
                         << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << "\n"
                         << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << "\n"
                         << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << "\n"
                         << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << "\n";
                }
            }
        }
    }

    // Escreve as faces (com cor)
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].show){
                    fout << "4 " << vertexIndex+0 << " " << vertexIndex+3 << " " << vertexIndex+2 << " " << vertexIndex+1 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << vertexIndex+4 << " " << vertexIndex+5 << " " << vertexIndex+6 << " " << vertexIndex+7 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << vertexIndex+0 << " " << vertexIndex+1 << " " << vertexIndex+5 << " " << vertexIndex+4 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << vertexIndex+0 << " " << vertexIndex+4 << " " << vertexIndex+7 << " " << vertexIndex+3 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << vertexIndex+3 << " " << vertexIndex+7 << " " << vertexIndex+6 << " " << vertexIndex+2 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << vertexIndex+1 << " " << vertexIndex+2 << " " << vertexIndex+6 << " " << vertexIndex+5 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    
                    vertexIndex += 8;
                }
            }
        }
    }

    fout.close();
}
