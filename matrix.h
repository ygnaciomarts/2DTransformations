#ifndef MATRIX_H
#define MATRIX_H
#include<math.h>

class Matrix
{

    int col, ren;
    float **Mat;

    public:

       Matrix(int nr=4,int nc=4, float valor=0);//constructor con arg. por defecto

       Matrix(float nr,float nc, float **m);

       Matrix(Matrix &);//CONSTRUCTOR DE COPIA
       ~Matrix();//DESTRUCTOR
       void SET(int R, int C, float val){Mat[R][C]=val;}
       float GET(int R, int C){return Mat[R][C];}
       int numCol(){return col;}
       int numRen(){return ren;}
       void Inicializa(int, int);
       double convertir(int grados);
       Matrix &operator *=(Matrix &mat2);
//EXISTE LA SOBRECARGA DE OPERADORES EN JAVA
       Matrix &operator*(const Matrix &m1);

       Matrix operator*(float);//Multiplicar por un escalar

       Matrix &operator=(Matrix &m);

       Matrix & asignar(Matrix);

       Matrix & Identidad();//PERMITE INICIALIZAR LA MATRIZ BASE

       //TRANSFORMACIONES
     //FigTransf       //Fig   //id   //Tx //Ty
    Matrix &traslacion(Matrix,Matrix,int,int);
                                     //Sx  //Sy
    Matrix &escalacion(Matrix,Matrix,double,double);

    Matrix &escalacionPF(Matrix,Matrix,double,double,double,double);
    Matrix &rotacion(Matrix,Matrix,double);
    Matrix &rotacionInversa(Matrix,Matrix,double);
    Matrix &rotacionPF(Matrix,Matrix,double,double,double);
};

#endif // MATRIX_H
