#include "mapeo.h"
#include <math.h>

/*Mapeo::Mapeo()
{

}
*/


void Mapeo::ventana(float wx1, float wy1, float wx2, float wy2)
{
    xWmin = wx1;
    yWmin = wy1;
    xWmax = wx2;
    yWmax = wy2;

}

void Mapeo::puerto(int pvx1, int pvy1, int pvx2, int pvy2)
{
    xpVMin = pvx1;
    ypVMin = pvy1;
    xpVMax = pvx2;
    ypVMax = pvy2;
}

void Mapeo::mapear(int xW, int yW, int &xp, int &yp, int L, int M)
{
   float sX,sY;
   sX = (xpVMax-xpVMin)/(xWmax-xWmin);//ESCALACION EN X
   //cout<<"Escalación en X = "<<sX<<endl;

   sY = (ypVMax-ypVMin)/(yWmax-yWmin);//ESCALACION EN Y
   //cout<<"Escalación en Y = "<<sY<<endl;
   xp =  int(round(sX*(xW-xWmin)+xpVMin+L) );
   yp = int(round(sY * (yWmin - yW) - ypVMin + M));

   // NOTA :   L y M REPRESENTAN EL ORIGEN
   //        A PARTIR DEL CUAL VAMOS A DIBUJAR
}





