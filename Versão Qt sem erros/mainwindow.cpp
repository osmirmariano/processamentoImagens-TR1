#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->W     = 800;
    this->H     = 600;
    this->save  = 0;

    this->imagem.load("C:/Users/osmir/Desktop/Restaurar_Imagem/cg.jpg");
    this->imagem_original = this->imagem;
    ui->label->setGeometry(QRect(10, 10, 800, 600));
    ui->label->setPixmap(QPixmap::fromImage(imagem));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Cinza(){

    int r,g,b,cinza;
    QColor pix;

    for (int x = 0; x < imagem.width(); x++) {
        for (int y = 0; y < imagem.height(); y++) {
            pix     = this->imagem.pixelColor(x,y);
            r       = pix.red();
            g       = pix.green();
            b       = pix.blue();
            cinza   = (r+g+b)/3;

            this->imagem.setPixel(x,y,QColor(cinza,cinza,cinza).rgb());
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(imagem));
}

void MainWindow::Ampliar(){

    QImage img;
    QColor cor;
    int w,h,X,Y,r[4],g[4],b[4];
    w = this->imagem.width() * 2;
    h = this->imagem.height() * 2;
    img = QImage(w,h,QImage::Format_RGB32);

    if( ui->vizinho->isChecked() ) {                    // VIZINHOS PROXIMOS

        for (int x = 0; x < w/2; x++) {
            for (int y = 0; y < h/2; y++) {
                X = (x*2);
                Y = (y*2);

                cor = this->imagem.pixelColor(x,y);
                img.setPixel( X, Y, cor.rgb() );
                img.setPixel( X+1, Y, cor.rgb() );
                img.setPixel( X, Y+1, cor.rgb() );
                img.setPixel( X+1, Y+1, cor.rgb() );
            }
        }
    }
    else if( ui->bilinear->isChecked() ) {              // BILINEAR

        for (int x = 0; x < w/2; x++) {
            for (int y = 0; y < h/2; y++) {

                X = (x*2);
                Y = (y*2);

                cor     = this->imagem.pixelColor(x,y);
                r[0]    = cor.red();
                g[0]    = cor.green();
                b[0]    = cor.blue();
                img.setPixel( X, Y, cor.rgb() );

                cor     = this->imagem.pixelColor(x,y+1);
                r[1]    = cor.red();
                g[1]    = cor.green();
                b[1]    = cor.blue();
                img.setPixel( X, Y+2, cor.rgb() );

                cor.setRed(     ( r[0] + r[1] )/2 );
                cor.setGreen(   ( g[0] + g[1] )/2 );
                cor.setBlue(    ( b[0] + b[1] )/2 );
                img.setPixel( X+1, Y+1, cor.rgb() );                    // A

                cor     = this->imagem.pixelColor(x+1,y);
                r[1]    = cor.red();
                g[1]    = cor.green();
                b[1]    = cor.blue();
                img.setPixel( X+2, Y, cor.rgb() );

                cor.setRed(     ( r[0] + r[1] )/2 );
                cor.setGreen(   ( g[0] + g[1] )/2 );
                cor.setBlue(    ( b[0] + b[1] )/2 );
                img.setPixel( X+1, Y, cor.rgb() );                      // B

                cor     = this->imagem.pixelColor(x+1,y+1);
                r[0]    = cor.red();
                g[0]    = cor.green();
                b[0]    = cor.blue();
                img.setPixel( X+2, Y+2, cor.rgb() );

                cor.setRed(     ( r[0] + r[1] )/2 );
                cor.setGreen(   ( g[0] + g[1] )/2 );
                cor.setBlue(    ( b[0] + b[1] )/2 );
                img.setPixel( X+2, Y+1, cor.rgb() );                    // E

                cor     = this->imagem.pixelColor(x,y+1);
                r[1]    = cor.red();
                g[1]    = cor.green();
                b[1]    = cor.blue();

                cor.setRed(     ( r[0] + r[1] )/2 );
                cor.setGreen(   ( g[0] + g[1] )/2 );
                cor.setBlue(    ( b[0] + b[1] )/2 );
                img.setPixel( X+1, Y+2, cor.rgb() );                    // D

                cor     = img.pixelColor(X,Y+1);
                r[0]    = cor.red();
                g[0]    = cor.green();
                b[0]    = cor.blue();

                cor     = img.pixelColor(X+1,Y);
                r[1]    = cor.red();
                g[1]    = cor.green();
                b[1]    = cor.blue();

                cor     = img.pixelColor(X+1,Y+2);
                r[2]    = cor.red();
                g[2]    = cor.green();
                b[2]    = cor.blue();

                cor     = img.pixelColor(X+2,Y+1);
                r[3]    = cor.red();
                g[3]    = cor.green();
                b[3]    = cor.blue();

                cor.setRed(     ( r[0] + r[1] + r[2] + r[3] )/4 );
                cor.setGreen(   ( g[0] + g[1] + g[2] + g[3] )/4 );
                cor.setBlue(    ( b[0] + b[1] + b[2] + b[3] )/4 );
                img.setPixel( X+1, Y+1, cor.rgb() );                    // C

            }
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
    this->imagem = img;
}

void MainWindow::Reduzir(){

    QImage img;
    QColor pix;
    int w,h,r[4],g[4],b[4],media[3],X,Y;
    w = this->imagem.width() / 2;
    h = this->imagem.height() / 2;
    img = QImage(w,h,QImage::Format_RGB32);

    if( ui->vizinho->isChecked() ) {                    // VIZINHOS PROXIMOS

        for (int x = 0; x < w*2; x = x + 2) {
            for (int y = 0; y < h*2; y = y + 2) {
                pix = this->imagem.pixelColor(x,y);
                img.setPixel( x/2, y/2 , pix.rgb() );
            }
        }

    }
    else if( ui->bilinear->isChecked() ) {              // BILINEAR

        for (int x = 0; x < w*2; x = x + 2) {
            for (int y = 0; y < h*2; y = y + 2) {
                X           = x / 2;
                Y           = y / 2;

                pix         = this->imagem.pixelColor(x,y);
                r[0]        = pix.red();
                g[0]        = pix.green();
                b[0]        = pix.blue();

                pix         = this->imagem.pixelColor(x+1,y);
                r[1]        = pix.red();
                g[1]        = pix.green();
                b[1]        = pix.blue();

                pix         = this->imagem.pixelColor(x,y+1);
                r[2]        = pix.red();
                g[2]        = pix.green();
                b[2]        = pix.blue();

                pix         = this->imagem.pixelColor(x+1,y+1);
                r[3]        = pix.red();
                g[3]        = pix.green();
                b[3]        = pix.blue();

                media[0]    = (r[0] + r[1] + r[2] + r[3])/4;
                media[1]    = (g[0] + g[1] + g[2] + g[3])/4;
                media[2]    = (b[0] + b[1] + b[2] + b[3])/4;

                img.setPixel(X,Y,QColor(media[0],media[1],media[2]).rgb());
            }
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
    this->imagem = img;
}

void MainWindow::on_pushButton_clicked()
{
    QString dimensoes;
    if ( ui->radioButton->isChecked() ){            // AMPLIAÇÃO

        Ampliar();

    }
    else if ( ui->radioButton_2->isChecked() ){     // NORMAL

        this->imagem = this->imagem_original;
        ui->label->setPixmap(QPixmap::fromImage(imagem));
        ui->pushButton_2->setEnabled(true);

    }
    else if ( ui->radioButton_3->isChecked() ){     // REDUÇÃO

        Reduzir();

    }
    W           = this->imagem.width();
    H           = this->imagem.height();
    dimensoes   = "Width: " + QString::number(W) + "\nHeigth: " + QString::number(H);
    ui->label_3->setText(dimensoes);
}

void MainWindow::on_pushButton_2_clicked()
{
    Cinza();
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString caminho,nome,ext,dimensoes;
    caminho = "D:/Documentos/FACULDADE/6º PERIODO/Processamento de Imagem/Restaurar_Imagem/";
    nome = ui->lineEdit->text();
    ext = ".jpg";

    this->imagem.load(caminho+nome+ext);
    this->imagem_original = this->imagem;
    ui->label->setPixmap(QPixmap::fromImage(imagem));
    W           = this->imagem.width();
    H           = this->imagem.height();
    dimensoes   = "Width: " + QString::number(W) + "\nHeigth: " + QString::number(H);
    ui->label_3->setText(dimensoes);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString pict;

    pict = "D:/Documentos/FACULDADE/6º PERIODO/Processamento de Imagem/Restaurar_Imagem/Save" + QString::number(save++) + ".jpg";
    this->imagem.save(pict);

//    pict = "Save" + QString::number(save++) + ".jpg";
//    const char *c = pict.toLatin1().constData();                      || ABRIR ARQUIVO SALVO ||
//    ui->label_3->setText(c);
//    system(c);
}
