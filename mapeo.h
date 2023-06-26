#ifndef MAPEO_H
#define MAPEO_H

#include <iostream>
using namespace std;

class Mapeo
{
    float xWmin,yWmin,xWmax,yWmax;
    int xpVMin,ypVMin, xpVMax, ypVMax;

public:
   // Mapeo();

    void ventana(float wx1, float wy1, float wx2, float wy2 );
    void puerto(int pvx1, int pvy1, int pvx2, int pvy2);
   //    &  nos da la referencia o direccion
    void mapear(int , int , int &xp, int &yp, int L, int M);
};

#endif // MAPEO_H
