#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QColorDialog>
#include <QtGui>

#include "mapeo.h"
#include "matrix.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void keyPressEvent(QKeyEvent *evento);
    void paintEvent(QPaintEvent *event) override;
    void asignarFigura();
    void dibujarFiguraMapeada();
    void trasladar(int tX, int tY);
    void escalar(double sX, double sY);
    void escalarPF(int tx, int ty, double sX, double sY);
    void rotacion(double angulo);
    void rotacionPF(int tx, int ty, double angulo);
    void calcularCentro();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void arcoiris();

    void animacion1();
    void animacion2();
    void animacion3();
    void animacion4();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_dial_valueChanged(int value);

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_30_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_checkBox_clicked();

private:
    Ui::Widget *ui;

    QTimer *timer1, *timer2, *timer3, *timer4, *timer5;
    QPainter *canvas;
    QPen pluma;

    //float Fig[4][3]; // int **Fig
    //float FigAux[4][3];

    float Fig[90][3]; // int **Fig
    float FigAux[90][3];

    int ancho;
    int centroX, centroY;

    int tX, tY;
    bool ani1, ani2;
    bool avanza;

    int valorCopia;
    float anchoZ, alturaZ;
    double centradoX, centradoY;
};
#endif // WIDGET_H
