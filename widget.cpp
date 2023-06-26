#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Inicialización de los timers
    timer1 = new QTimer();
    timer2 = new QTimer();
    timer3 = new QTimer();
    timer4 = new QTimer();
    timer5 = new QTimer();

    // Variable copia para la altura de la ventana
    alturaZ = size().height();

    // Conexión de los timers con las animaciones
    connect(timer1, SIGNAL(timeout()), this, SLOT(arcoiris()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(animacion1()));
    connect(timer3, SIGNAL(timeout()), this, SLOT(animacion2()));
    connect(timer4, SIGNAL(timeout()), this, SLOT(animacion3()));
    connect(timer5, SIGNAL(timeout()), this, SLOT(animacion4()));

    // Asignación de la figura
    asignarFigura();

    pluma.setWidth(2);

    // Valor de copia para el slider que nos permite
    // hacerle zoom al puerto de visión
    valorCopia = ui->horizontalSlider->value();
}


Widget::~Widget()
{
    delete ui;
}


// Evento de los botones para trasladar la figura
void Widget::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key() == Qt::Key_A) {
        trasladar(tX - ui->spinBox->value(), 0);
    } if(evento->key() == Qt::Key_D) {
        trasladar(tX + ui->spinBox->value(), 0);
    } if(evento->key() == Qt::Key_W) {
        trasladar(0, tY + ui->spinBox->value());
    } if(evento->key() == Qt::Key_S) {
        trasladar(0, tY - ui->spinBox->value());
    }

    repaint();
}


void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    canvas = new QPainter(this);
    dibujarFiguraMapeada();

    canvas->end();
}


// Método que asigna la figura, en este caso, el hongo
// de la saga de videojuegos de Mario Bros.
void Widget::asignarFigura()
{
    // Usar coords. homogéneas
    Fig[0][0]= 20 ; Fig[0][1]= 60; Fig[0][2]= 1; // A
    Fig[1][0]= 20 ; Fig[1][1]= 44; Fig[1][2]= 1; // B2
    Fig[2][0]= 32  ; Fig[2][1]= 44; Fig[2][2]= 1; // A2
    Fig[3][0]= 32   ; Fig[3][1]= 50; Fig[3][2]= 1; // Z1
    Fig[4][0]= 36   ; Fig[4][1]= 50; Fig[4][2]= 1; // W1
    Fig[5][0]= 36   ; Fig[5][1]= 64; Fig[5][2]= 1; // V1
    Fig[6][0]= 32   ; Fig[6][1]= 64; Fig[6][2]= 1; // U1
    Fig[7][0]= 32   ; Fig[7][1]= 70; Fig[7][2]= 1; // B1
    Fig[8][0]= 24   ; Fig[8][1]= 70; Fig[8][2]= 1; // C1
    Fig[9][0]= 24   ; Fig[9][1]= 60; Fig[9][2]= 1; // D1
    Fig[10][0]= 20   ; Fig[10][1]= 60; Fig[10][2]= 1; // Regreso a A
    Fig[11][0]= 20   ; Fig[11][1]= 30; Fig[11][2]= 1; // B
    Fig[12][0]= 44   ; Fig[12][1]= 30; Fig[12][2]= 1; // I1
    Fig[13][0]= 44   ; Fig[13][1]= 40; Fig[13][2]= 1; // J1
    Fig[14][0]= 96   ; Fig[14][1]= 40; Fig[14][2]= 1; // K1
    Fig[15][0]= 56   ; Fig[15][1]= 40; Fig[15][2]= 1; // M1
    Fig[16][0]= 56   ; Fig[16][1]= 28; Fig[16][2]= 1; // N1
    Fig[17][0]= 62   ; Fig[17][1]= 28; Fig[17][2]= 1; // 01
    Fig[18][0]= 62   ; Fig[18][1]= 40; Fig[18][2]= 1; // P1
    Fig[19][0]= 65   ; Fig[19][1]= 40; Fig[19][2]= 1; // S2
    Fig[20][0]= 65   ; Fig[20][1]= 45; Fig[20][2]= 1; // T2
    Fig[21][0]= 58   ; Fig[21][1]= 45; Fig[21][2]= 1; // U2
    Fig[22][0]= 58   ; Fig[22][1]= 65; Fig[22][2]= 1; // V2
    Fig[23][0]= 65   ; Fig[23][1]= 65; Fig[23][2]= 1; // W2
    Fig[24][0]= 65   ; Fig[24][1]= 70; Fig[24][2]= 1; // Z2
    Fig[25][0]= 73   ; Fig[25][1]= 70; Fig[25][2]= 1; // B3
    Fig[26][0]= 73   ; Fig[26][1]= 65; Fig[26][2]= 1; // A3
    Fig[27][0]= 80   ; Fig[27][1]= 65; Fig[27][2]= 1; // C3
    Fig[28][0]= 80   ; Fig[28][1]= 45; Fig[28][2]= 1; // D3
    Fig[29][0]= 73   ; Fig[29][1]= 45; Fig[29][2]= 1; // G3
    Fig[30][0]= 73   ; Fig[30][1]= 40; Fig[30][2]= 1; // F3
    Fig[31][0]= 76   ; Fig[31][1]= 40; Fig[31][2]= 1; // Q1
    Fig[32][0]= 76   ; Fig[32][1]= 28; Fig[32][2]= 1; // R1
    Fig[33][0]= 82   ; Fig[33][1]= 28; Fig[33][2]= 1; // S1
    Fig[34][0]= 82   ; Fig[34][1]= 40; Fig[34][2]= 1; // T1
    Fig[35][0]= 96   ; Fig[35][1]= 40; Fig[35][2]= 1; // K1
    Fig[36][0]= 96   ; Fig[36][1]= 30; Fig[36][2]= 1; // L1
    Fig[37][0]= 120   ; Fig[37][1]= 30; Fig[37][2]= 1; // K
    Fig[38][0]= 120   ; Fig[38][1]= 44; Fig[38][2]= 1; // R2
    Fig[39][0]= 108   ; Fig[39][1]= 44; Fig[39][2]= 1; // Q2
    Fig[40][0]= 108   ; Fig[40][1]= 50; Fig[40][2]= 1; // P2
    Fig[41][0]= 104   ; Fig[41][1]= 50; Fig[41][2]= 1; // O2
    Fig[42][0]= 104   ; Fig[42][1]= 64; Fig[42][2]= 1; // N2
    Fig[43][0]= 108   ; Fig[43][1]= 64; Fig[43][2]= 1; // M2
    Fig[44][0]= 108   ; Fig[44][1]= 70; Fig[44][2]= 1; // O
    Fig[45][0]= 108   ; Fig[45][1]= 76; Fig[45][2]= 1; // P
    Fig[46][0]= 100   ; Fig[46][1]= 76; Fig[46][2]= 1; // Q
    Fig[47][0]= 100   ; Fig[47][1]= 70; Fig[47][2]= 1; // L2
    Fig[48][0]= 90   ; Fig[48][1]= 70; Fig[48][2]= 1; // k2
    Fig[49][0]= 90   ; Fig[49][1]= 74; Fig[49][2]= 1; // j2
    Fig[50][0]= 84   ; Fig[50][1]= 74; Fig[50][2]= 1; // i2
    Fig[51][0]= 84   ; Fig[51][1]= 86; Fig[51][2]= 1; // H2
    Fig[52][0]= 56   ; Fig[52][1]= 86; Fig[52][2]= 1; // g2
    Fig[53][0]= 50   ; Fig[53][1]= 86; Fig[53][2]= 1; // U
    Fig[54][0]= 50   ; Fig[54][1]= 80; Fig[54][2]= 1; // V
    Fig[55][0]= 40   ; Fig[55][1]= 80; Fig[55][2]= 1; // w
    Fig[56][0]= 40   ; Fig[56][1]= 76; Fig[56][2]= 1; // z
    Fig[57][0]= 32   ; Fig[57][1]= 76; Fig[57][2]= 1; // a1
    Fig[58][0]= 32   ; Fig[58][1]= 70; Fig[58][2]= 1; // b1
    Fig[59][0]= 32   ; Fig[59][1]= 76; Fig[59][2]= 1; // regreso
    Fig[60][0]= 40   ; Fig[60][1]= 76; Fig[60][2]= 1; // z
    Fig[61][0]= 40   ; Fig[61][1]= 70; Fig[61][2]= 1; // c2
    Fig[62][0]= 50   ; Fig[62][1]= 70; Fig[62][2]= 1; // d2
    Fig[63][0]= 50   ; Fig[63][1]= 74; Fig[63][2]= 1; // e2
    Fig[64][0]= 56   ; Fig[64][1]= 74; Fig[64][2]= 1; // f2
    Fig[65][0]= 56   ; Fig[65][1]= 86; Fig[65][2]= 1; // g2
    Fig[66][0]= 84   ; Fig[66][1]= 86; Fig[66][2]= 1; // H2
    Fig[67][0]= 90   ; Fig[67][1]= 86; Fig[67][2]= 1; // t
    Fig[68][0]= 90   ; Fig[68][1]= 80; Fig[68][2]= 1; // s
    Fig[69][0]= 100   ; Fig[69][1]= 80; Fig[69][2]= 1; // r
    Fig[70][0]= 100   ; Fig[70][1]= 76; Fig[70][2]= 1; // Q
    Fig[71][0]= 108   ; Fig[71][1]= 76; Fig[71][2]= 1; // P
    Fig[72][0]= 108   ; Fig[72][1]= 70; Fig[72][2]= 1; // O
    Fig[73][0]= 116   ; Fig[73][1]= 70; Fig[73][2]= 1; // n
    Fig[74][0]= 116   ; Fig[74][1]= 60; Fig[74][2]= 1; // m
    Fig[75][0]= 120   ; Fig[75][1]= 60; Fig[75][2]= 1; // L
    Fig[76][0]= 120   ; Fig[76][1]= 44; Fig[76][2]= 1; // R2
    Fig[77][0]= 120   ; Fig[77][1]= 30; Fig[77][2]= 1; // K
    Fig[78][0]= 114   ; Fig[78][1]= 30; Fig[78][2]= 1; // j
    Fig[79][0]= 114   ; Fig[79][1]= 24; Fig[79][2]= 1; // i
    Fig[80][0]= 108   ; Fig[80][1]= 24; Fig[80][2]= 1; // h
    Fig[81][0]= 108   ; Fig[81][1]= 12; Fig[81][2]= 1; // g
    Fig[82][0]= 102   ; Fig[82][1]= 12; Fig[82][2]= 1; // g1
    Fig[83][0]= 102   ; Fig[83][1]= 4; Fig[83][2]= 1; // h1
    Fig[84][0]= 38   ; Fig[84][1]= 4; Fig[84][2]= 1; // f1
    Fig[85][0]= 38   ; Fig[85][1]= 12; Fig[85][2]= 1; // e1
    Fig[86][0]= 32   ; Fig[86][1]= 12; Fig[86][2]= 1; // f
    Fig[87][0]= 32   ; Fig[87][1]= 24; Fig[87][2]= 1; // e
    Fig[88][0]= 26   ; Fig[88][1]= 24; Fig[88][2]= 1; // d
    Fig[89][0]= 26   ; Fig[89][1]= 30; Fig[89][2]= 1; // c


    // Se respalda en el arreglo auxiliar
    for(int r=0; r < 90 ;r++ )
        for(int c = 0; c < 3; c++)
            FigAux[r][c] = Fig[r][c];

    // Establecemos el ancho
    ancho = this->size().width() - ui->widget->size().width();
    // Variable de copia para el zoom
    anchoZ = this->size().width() - ui->widget->size().width();

    // Se establece el centro del área del dibujo
    centroX = ancho / 2;
    centroY = this->size().height() / 2;

    tX = tY = 0;
}

// Se dibuja la figura ya mapeada, apoyándonos del método
// de Antialaising
void Widget::dibujarFiguraMapeada()
{
    canvas->setRenderHint(QPainter::Antialiasing, true);

    // Pluma que se usará para pintar los cuadrantes
    QPen pen(QColor(95, 95, 95),3);
    canvas->setPen(pen);

    // Se establecen los 4 cuadrantes
    canvas->drawLine(0,size().height()/2,ancho,size().height()/2);
    canvas->drawLine(ancho/2,0,ancho/2,size().height());

    Mapeo dibujo;

    // Para la escalación 1 : 1
    dibujo.ventana(0,0,ancho, size().height());
    dibujo.puerto(0,0,anchoZ,alturaZ);

    // Para la escalación 1 : 0.5
    //dibujo.ventana(0,0,ancho, size().height());
    //dibujo.puerto(0,0,ancho/2,size().height()/2);

    // Pluma que puede variar según lo desee el usuario
    canvas->setPen(pluma);

    // Origen de la figura
    // Dibujar en el centro del canvas
    int L = centroX;
    int M = centroY;

    // Variables para manejar los vértices de la figura
    int x1,y1, x2,y2;

    for(int i = 0; i < 89; i++) {
        dibujo.mapear(Fig[i][0],  Fig[i][1],x1,y1,L,M);
        dibujo.mapear(Fig[i+1][0],Fig[i+1][1], x2, y2, L,M);
        canvas->drawLine(x1,y1,x2,y2);
    }
}


// Transformaciones 2D
// > Traslación
void Widget::trasladar(int tX, int tY)
{
    Matrix fig, id, figTransf;

    fig.Inicializa(90, 3); // Usar la cantidad de renglones de la figura a utilizar
    id.Inicializa(3, 3);
    figTransf.Inicializa(90, 3);

    // Asignar los puntos de la figura
    for(int i=0; i < fig.numRen(); i++)
        for(int j=0; j < fig.numCol(); j++)
            fig.SET(i, j, Fig[i][j]);

    // Aplicar la matriz de traslación
    figTransf.traslacion(fig,id,tX,tY);

    for(int r=0; r < figTransf.numRen(); r++)
        for(int c=0; c < figTransf.numCol(); c++)
            Fig[r][c] = figTransf.GET(r,c);

    // Actualizamos el canvas
    this->repaint();
}

// > Escalación
void Widget::escalar(double sX, double sY)
{
    Matrix fig, id, figT;

    fig.Inicializa(90,3); // Usar la cantidad de renglones de la figura a utilizar
    id.Inicializa(3,3);
    figT.Inicializa(90,3);

    // Asignar los puntos de la figura
    for(int i=0; i < fig.numRen(); i++)
        for(int j = 0; j < fig.numCol(); j++)
            fig.SET(i,j,Fig[i][j]);

    // Aplicar escalación
    figT.escalacion(fig, id, sX, sY);

    // Asignar a la fig. original/que se dibujará
    for(int r=0; r < figT.numRen(); r++)
        for(int c=0; c < figT.numCol(); c++)
            Fig[r][c] = figT.GET(r, c);

    // Actualizamos el canvas
    this->repaint();
}


// > Escalación (por punto fijo)
void Widget::escalarPF(int tx, int ty, double sX, double sY)
{
    Matrix fig, id, figT;

    fig.Inicializa(90,3); // Usar la cantidad de renglones de la figura a utilizar
    id.Inicializa(3,3);
    figT.Inicializa(90,3);

    // Asignar los puntos de la figura
    for (int i = 0; i < fig.numRen(); ++i)
        for (int j = 0; j < fig.numCol(); ++j)
            fig.SET(i,j,Fig[i][j]);

    // Aplicar escalación
    figT.escalacionPF(fig,id,tx,ty,sX,sY);

    // Asignar a la fig. original/que se dibujará
    for (int ren = 0; ren < figT.numRen(); ++ren)
        for (int col = 0; col < figT.numCol(); ++col)
            Fig[ren][col] = figT.GET(ren,col);

    // Actualizamos el canvas
    this->update();
}


// > Rotación
void Widget::rotacion(double angulo)
{
    Matrix fig, id, figT;

    fig.Inicializa(90,3); // Usar la cantidad de renglones de la figura a utilizar
    id.Inicializa(3,3);
    figT.Inicializa(90,3);

    // Asignar los puntos de la figura
    for (int i = 0; i < fig.numRen(); ++i)
        for (int j = 0; j < fig.numCol(); ++j)
            fig.SET(i,j,Fig[i][j]);

    // Aplicar rotación
    figT.rotacion(fig,id,angulo);

    // Asignar a la fig. original/que se dibujará
    for (int ren = 0; ren < figT.numRen(); ++ren)
        for (int col = 0; col < figT.numCol(); ++col)
            Fig[ren][col] = figT.GET(ren,col);

    // Actualizamos el canvas
    this->update();
}


// > Rotación (por punto fijo)
void Widget::rotacionPF(int tx, int ty, double angulo)
{
    Matrix fig, id, figT;

    fig.Inicializa(90,3); // Usar la cantidad de renglones de la figura a utilizar
    id.Inicializa(3,3);
    figT.Inicializa(90,3);


    // Asignar los puntos de la figura
    for (int i = 0; i < fig.numRen(); ++i)
        for (int j = 0; j < fig.numCol(); ++j)
            fig.SET(i,j,Fig[i][j]);

    // Aplicar rotación
    figT.rotacionPF(fig, id, tx, ty, angulo);

    // Asignar a la fig. original/que se dibujará
    for (int ren = 0; ren < figT.numRen(); ++ren)
        for (int col = 0; col < figT.numCol(); ++col)
            Fig[ren][col] = figT.GET(ren,col);

    // Actualizamos el canvas
    this->update();
}


// Animación 1
void Widget::animacion1() // Vista en clase
{
    static bool dir = true;
    static int angulo = 0;
    static int cont = 0;

    if(cont <= 8 && dir == true) {
        angulo = 90;
        double pfx = 20;
        double pfy = 20;
        rotacionPF(pfx, pfy, angulo);
        cont++;

        if(cont == 8) {
            // Reiniciamos los valores
            angulo = 0;
            cont = 0;
            dir = false;
        }
    } if(!dir) {
        angulo = -90;
        double pfx = 20;
        double pfy = 20;
        rotacionPF(pfx, pfy, angulo);
        cont++;
        if(cont == 8) {
            angulo = 0;
            cont = 0;
            dir = true;
        }
    }
}


// Traslación horizontal (positiva)
void Widget::on_pushButton_3_clicked()
{
    trasladar(tX + ui->spinBox->value(), 0);
}


// Traslación horizontal (negativa)
void Widget::on_pushButton_4_clicked()
{
    trasladar(tX - ui->spinBox->value(), 0);
}


// Traslación vertical (positiva)
void Widget::on_pushButton_clicked()
{
    trasladar(0, tY + ui->spinBox_2->value());
}


// Traslación vertical (negativa)
void Widget::on_pushButton_2_clicked()
{
    trasladar(0, tY - ui->spinBox_2->value());
}


// Resetear la figura
void Widget::on_pushButton_5_clicked()
{
    for(int ren = 0; ren < 90; ren++)
        for(int col = 0; col < 3; col++)
            Fig[ren][col] = FigAux[ren][col];

    tX = tY = 0;
    update();
}


// Prueba inicial de un método para el efecto arcoíris de
// la figura
/*void Widget::arcoiris()
{
    int r = 255;
    int g = 1;
    int b = 255;

    //while(band) {
        while(g != 255) {
            r--;
            g++;
            b--;

            //if(g == 255) {
                //r--;
            //}

            if(r == 0) {
                r++;
                g--;
                b++;
            }

            pluma.setColor(QColor(r,g,b));
            repaint();
            //r--;
        }
        //pluma.setColor(QColor(i,10,20));
        //update();
    //}

    //for(r=255; r < 0; r--) {
        //for(g=1; g >= 255; g++) {
            //for(b=1; b >= 255; b++) {
                //pluma.setColor(QColor(r,g,b));
                //repaint();
            //}
        //}
    //}

    //band = false;
}*/

/*void Widget::arcoiris() {
    int r = 1;
    int g = 1;
    int b = 1;
    int seq = 1;

    while(seq != 0) {

    if (seq == 6) {
        b--;
        if (b == 0)
            seq = 1;
    }
    if (seq == 5) {
        r++;
        if (r == 12)
            seq = 6;
    }
    if (seq == 4) {
        g--;
        if (g == 0)
            seq = 5;
    }
    if (seq == 3) {
        b++;
        if (b == 12)
            seq = 4;
    }
    if (seq == 2) {
        r--;
        if (r == 0)
            seq = 3;
    }
    if (seq == 1) {
        g++;
        if (g == 12)
            seq = 2;
    }

    pluma.setColor(QColor(r,g,b));
    repaint();

    seq--;

    }
}*/


// Animación 2
void Widget::animacion2() // Propia, simula cuando Mario saca el hongo del
{                         // bloque y este comienza a moverse
    static bool dir = true;
    static bool band = false;
    static int i = 0;

    // Caminado hacia la derecha
    if(dir == true) {
        static double tX = 5;
        static double tY = 0;
        trasladar(tX,tY);
        i++;

        if(i == 60) {
            i = 0;
            dir = false;
            band = true;
        }
    // Caminado hacia la izquierda
    } if(band==true){
        static double tX = -5;
        static double tY = 0;
        trasladar(tX,tY);
        i++;

        if(i == 60) {
            i = 0;
            dir = true;
            band = false;
        }
    }
}


// Animación 3
void Widget::animacion3() // Propia, simula cuando Mario ingiere el hongo
{
    static bool aumento = true;
    static bool band1 = false;
    static bool band2 = false;
    static bool band3 = false;
    static bool band4 = false;
    static int i = 0;

    // Escala a 1.2, para "simular" que creció
    if(aumento == true) {
        escalar(1.2,1.2);
        i++;

        if(i == 2) {
            i = 0;
            aumento = false;
            band1 = true;
            band2 = false;
            band3 = false;
            band4 = false;
        }
    // Escala a 0.8, para "simular" que se hizo pequeño
    // (con el fin de dar el efecto)
    } if(band1 == true) {
        escalar(0.8,0.8);
        i++;

        if(i == 3) {
            i = 0;
            aumento = false;
            band1 = false;
            band2 = true;
            band3 = false;
            band4 = false;
        }
    // Escala a 1.4, para "simular" que creció
    } if(band2 == true) {
        escalar(1.4,1.4);
        i++;

        if(i == 2) {
            i = 0;
            aumento = false;
            band1 = false;
            band2 = false;
            band3 = true;
            band4 = false;
        }
    // Escala a 0.8, para "simular" que se hizo pequeño
    // (con el fin de dar el efecto)
    } if(band3 == true) {
        escalar(0.8,0.8);
        i++;

        if(i == 3) {
            i = 0;
            aumento = false;
            band1 = false;
            band2 = false;
            band3 = false;
            band4 = true;
        }
    // Escala a 1.6, para "simular" que creció
    } if(band4 == true) {
        escalar(1.6,1.6);
        i++;

        if(i == 2) {
            i = 0;
            aumento = false;
            band1 = false;
            band2 = false;
            band3 = false;
            band4 = false;
        }
    }

    repaint();
}


// Animación 4
void Widget::animacion4() // Copia del método animacion3() para evitar
{                         // problemas con el timer
    static bool aumento = true;
    static bool band1 = false;
    static bool band2 = false;
    static bool band3 = false;
    static bool band4 = false;
    static int i = 0;

    // Escala a 1.2, para "simular" que creció
    if(aumento == true) {
        escalar(1.2,1.2);
        i++;

        if(i == 2) {
            i = 0;
            aumento = false;
            band1 = true;
            band2 = false;
            band3 = false;
            band4 = false;
        }
    // Escala a 0.8, para "simular" que se hizo pequeño
    // (con el fin de dar el efecto)
    } if(band1 == true) {
        escalar(0.8,0.8);
        i++;

        if(i == 3) {
            i = 0;
            aumento = false;
            band1 = false;
            band2 = true;
            band3 = false;
            band4 = false;
        }
    // Escala a 1.4, para "simular" que creció
    } if(band2 == true) {
        escalar(1.4,1.4);
        i++;

        if(i == 2) {
            i = 0;
            aumento = false;
            band1 = false;
            band2 = false;
            band3 = true;
            band4 = false;
        }
    // Escala a 0.8, para "simular" que se hizo pequeño
    // (con el fin de dar el efecto)
    } if(band3 == true) {
        escalar(0.8,0.8);
        i++;

        if(i == 3) {
            i = 0;
            aumento = false;
            band1 = false;
            band2 = false;
            band3 = false;
            band4 = true;
        }
    // Escala a 1.6, para "simular" que creció
    } if(band4 == true) {
        escalar(1.6,1.6);
        i++;

        if(i == 2) {
            i = 0;
            aumento = false;
            band1 = false;
            band2 = false;
            band3 = false;
            band4 = false;
        }
    }

    repaint();
}


// Método "arcoíris", el cual, simula la estrella de la
// saga de videojuegos, aplicando el efecto arcoíris en
// el borde de la figura con ayuda de un timer
void Widget::arcoiris() {
    if(timer1->isActive()) {
        pluma.setColor(QColor(rand()%ui->vsIntensidadR->value(),rand()%ui->vsIntensidadG->value(),rand()%ui->vsIntensidadB->value()));
        repaint();
    }
}


// Inicialización/detención de timers
void Widget::on_pushButton_6_clicked()
{
    timer1->start(80);
}


void Widget::on_pushButton_7_clicked()
{
    timer1->stop();
}


// Dial que cambia el grosor de la figura
void Widget::on_dial_valueChanged(int value)
{
    pluma.setWidth(value);
    update();
}


// Botón que abre un selector de colores para el
// borde de la figura
void Widget::on_pushButton_18_clicked()
{
    QColor seleccionaColor = QColorDialog::getColor(Qt::white, this, "Selecciona un color");

    if(seleccionaColor.isValid()) {
        pluma.setColor(seleccionaColor);
    }
}


// Escalación 2D
// Botones que alteran la figura original
// (escalación, traslación, rotación)
void Widget::on_pushButton_19_clicked()
{
    double sX = ui->doubleSpinBox->value();
    double sY = ui->doubleSpinBox_2->value();
    escalar(sX, sY);
}


void Widget::on_doubleSpinBox_valueChanged(double sX)
{
    escalar(sX, 1);
}


void Widget::on_doubleSpinBox_2_valueChanged(double sY)
{
    escalar(1, sY);
}


void Widget::on_pushButton_20_clicked()
{
    trasladar(-60, -60);
}


void Widget::on_pushButton_21_clicked()
{
    escalar(2, 2);
}


void Widget::on_pushButton_22_clicked()
{
    trasladar(60, 60);
}


void Widget::on_pushButton_23_clicked()
{
    escalarPF(20, 20, ui->doubleSpinBox->value(), ui->doubleSpinBox_2->value());
}


void Widget::on_pushButton_24_clicked()
{
    int angulo = ui->spinBox_3->value();
    rotacion(angulo);
}


void Widget::on_pushButton_25_clicked()
{
    int angulo = ui->spinBox_3->value();
    rotacionPF(20, 20, angulo);
    update();
}


void Widget::on_pushButton_26_clicked()
{
    timer2->start(100);
}


void Widget::on_pushButton_27_clicked()
{
    trasladar(-150,0);

    timer5->start(85);
    timer3->start(25);
}


void Widget::on_pushButton_31_clicked()
{
    timer2->stop();
}


void Widget::on_pushButton_30_clicked()
{
    timer3->stop();
}


// Método que calcula el centro del eje, para poder hacer
// zoom en el puerto
void Widget::calcularCentro()
{
    centradoX = (Fig[0][0]+Fig[1][0]+Fig[2][0])/3.0;
    centradoY = (Fig[0][1]+Fig[1][1]+Fig[2][1])/3.0;
}


// Slider de zoom, el cual, altera el puerto de visión
// original de la figura
void Widget::on_horizontalSlider_valueChanged(int value)
{
    calcularCentro();
    int valorCalculado;
    if(value > valorCopia){
        valorCalculado = valorCopia-value;
        alturaZ-=valorCalculado * 8;
        anchoZ -=valorCalculado * 10;
    }
    if(value < valorCopia){
        valorCalculado = value-valorCopia;
        anchoZ+= valorCalculado * 10;
        alturaZ+=valorCalculado * 8;
    }
    valorCopia = value;
    repaint();
}


void Widget::on_pushButton_28_clicked()
{
    timer4->start(90);
}


void Widget::on_pushButton_29_clicked()
{
    ui->pushButton_5->click();
    timer4->stop();
}


void Widget::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
        ui->widget->setEnabled(false);
    else
        ui->widget->setEnabled(true);
}

