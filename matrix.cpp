#include "matrix.h"
#include <math.h>
#include <assert.h>

Matrix::Matrix(int nr,int nc, float valor)
{
  ren = nr;
  col = nc;
  Mat = new float*[ren];//VECTOR DE PUNTEROS
  assert(Mat);//SI DA NULL VA A TERMINAR CON UN ERROR, PARECIDO A UN TRY CATCHT
  for(int i = 0; i < ren; i++)
  {
      Mat[i] = new float[col];
      assert(Mat[i]);
  }

  for(int i = 0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = valor;
}

Matrix::Matrix(float nr,float nc, float **m)
{
  ren = nr;
  col = nc;
  Mat = new float*[ren];
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
      Mat[i] = new float[col];
      assert(Mat[i]);
  }

  for(int i = 0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = m[i][j];
}


//CONSTRUCTOR DE COPIA

Matrix::Matrix(Matrix &m)
{
   this->ren=m.numRen();
   col=m.numCol();
   Mat =new float*[ren];
   for(int i = 0; i < ren; i++)
  {
     Mat[i] = new float[col];
     assert(Mat[i]);
  }
   for(int i=0; i<ren; i++)
      for( int j=0; j<col; j++)
         Mat[i][j]=m.GET(i,j);
}

void Matrix::Inicializa(int R, int C)
{
   col=C;
   ren=R;
   Mat=new float *[ren];
   for(int i=0; i<ren; i++)
      Mat[i]=new float[col];
   for(int i=0; i<ren; i++)
      for(int j=0; j<col; j++)
          Mat[i][j]=0;
}

double Matrix::convertir(int grados)
{
    double resultado;
    resultado= (M_PI/180)*grados;
    return resultado;
}

Matrix &Matrix::operator*=(Matrix &mat2)
{
   Matrix aux;
   aux.Inicializa(ren, mat2.numCol());


   for(int i=0; i<ren; i++)
   {
      for(int j=0; j<mat2.numCol(); j++)
      {
         float suma=0;
        // Mat[i][j]=0;
         for(int k=0; k<col; k++)
         {
           suma+=floor(Mat[i][k]*mat2.GET(k,j)+0.5);
           aux.SET(i,j,suma);
         }
         //aux.SET(i,j,suma);
      }
   }
   asignar(aux);
   return *this;
}

Matrix Matrix::operator*(float val)
{
   Matrix temp;
   temp.Inicializa(ren,col);
   for(int i=0; i<ren;i++)
      for(int j=0; j<col; j++)
         temp.SET(i,j,Mat[i][j]* val);
   return temp;
}


Matrix &Matrix::operator*(const Matrix &m1)
{
  //assert((ren == m1.ren) && (col == m1.col));
   Matrix * result = new Matrix(ren,col,0);
   assert(result);
   for(int i=0; i < ren; i++)
     for(int j = 0;  j < col; j++)
                       //DEBE SER EL NUMERO DE COLUMNAS
                     //REN SOLO SI ES CUADRADA EJ: 3 x 3
       for(int k = 0; k < col; k++)
            //result->Mat[i][j]= result->Mat[i][j] + Mat[i][k] * m1.Mat[k][j];
           result->Mat[i][j] += Mat[i][k] * m1.Mat[k][j];


   return *result;
}

Matrix &Matrix::operator=(Matrix &m)
{
//eliminar el tamaño de la matriz destino
  for(int i= 0; i<ren;i++ )
     //Se borran los renglones de la matriz
       delete [] Mat[i];
  //Se borra el arreglo de punteros
  delete []Mat;
//Asignar los nuevos datos de la matriz que llego
  ren=m.numRen();
  col = m.numCol();
  Mat = new float*[ren];
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
     Mat[i] = new float[col];
     assert(Mat[i]);
  }
  for( int i =0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = m.Mat[i][j];

  return *this;
}


Matrix &Matrix::asignar(Matrix m)
{
   for(int i=0;i<m.numRen();i++)
       for(int j=0;j<m.numCol();j++)
                Mat[i][j]=m.GET(i,j);
   return *this;
}

Matrix::~Matrix()
{
  //Se libera la memoria
  for(int i= 0; i<ren;i++ )
     //Se borran los renglones de la matriz
       delete [] Mat[i];
  //Se borra el arreglo de punteros
  delete []Mat;

}

Matrix &Matrix::Identidad()
{
  for(int i=0; i < ren; i++)
    for( int j = 0; j < col; j++)
      if( i == j)
         Mat[i][i]= 1;
      else
         Mat[i][j]= 0;
  return *this;
}
// ----------------------- Transformaciones
Matrix &Matrix::traslacion(Matrix f, Matrix id, int tX, int tY)
{
id.Identidad();
id.SET(2,0,tX);
id.SET(2,1,tY);

f *= id;
this->asignar(f);
return *this;// SE REGRESA LA FIGURA TRANSFORMADA
}

Matrix &Matrix::escalacion(Matrix f, Matrix id, double sX, double sY)
{
 id.Identidad();
 id.SET(0,0,sX);
 id.SET(1,1,sY);

 f*=id;
 this->asignar(f);
 return *this;
}

Matrix &Matrix::escalacionPF(Matrix f, Matrix id, double tX, double tY, double sX, double sY)
{
    id.Identidad();
    id.SET(0,0,sX);
    id.SET(1,1,sY);
    id.SET(2,0,-tX*(sX-1));
    id.SET(2,1,-tY*(sY-1));

    f*=id;
    this->asignar(f);
    return *this;
}

Matrix &Matrix::rotacion(Matrix f, Matrix id, double grados)
{
    double radianes= convertir(grados);

    id.Identidad();
    id.SET(0,0,cos(radianes));
    id.SET(0,1,sin(radianes));
    id.SET(1,0,-sin(radianes));
    id.SET(1,1,cos(radianes));

    f*=id;
    this->asignar(f);
    return *this;
}

Matrix &Matrix::rotacionInversa(Matrix f, Matrix id, double grados)
{
    double radianes= convertir(grados);

    id.Identidad();
    id.SET(0,0,cos(radianes));
    id.SET(0,1,-sin(radianes));
    id.SET(1,0,sin(radianes));
    id.SET(1,1,cos(radianes));

    f*=id;
    this->asignar(f);
    return *this;
}

Matrix &Matrix::rotacionPF(Matrix f, Matrix id, double grados,double tX,double tY)
{
    double radianes= convertir(grados);

    id.Identidad();
    id.SET(0,0,cos(radianes));
    id.SET(0,1,sin(radianes));
    id.SET(1,0,-sin(radianes));
    id.SET(1,1,cos(radianes));
    id.SET(2,0,-tX*(cos(radianes)-1)+(tY*sin(radianes)));
    id.SET(2,1,-tX*sin(radianes)-(tY*(cos(radianes)-1)));

    f*=id;
    this->asignar(f);
    return *this;
}

