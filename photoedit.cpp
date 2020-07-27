#include "photoedit.h"
#include "ui_photoedit.h"
#include <QDesktopWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QPen>

#define OFFSETY         50
#define NOMBREVENTANA   "Editor de fotos"


Photoedit::Photoedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Photoedit)
{
    ui->setupUi(this);
    mImage = nullptr;
    mPainter = nullptr;
    mEnabled = false;
    mCutImage = nullptr;
    mImagePrev = nullptr;
    pathImage = nullptr;
}

Photoedit::Photoedit(QWidget *parent, const QString &image):
    QDialog(parent),
    ui(new Ui::Photoedit)
{
    ui->setupUi(this);
    pathImage = new QString(image);
    mImg = new QImageReader(image);
    QSize aux(1080,720);
    mImg->setScaledSize(aux);
    mImage = new QImage(mImg->read());
    this->setWindowTitle(NOMBREVENTANA);
    this->setFixedSize(1080,720);
    mPainter = new QPainter(mImage);
    pen = new QPen(Qt::black);
    pen->setCapStyle(Qt::RoundCap);
    pen->setWidth(3);
    mEnabled = false;
    mCutImage = nullptr;
    mImagePrev = nullptr;
    refreshOffset();

    connect(ui->PB_retroceder, SIGNAL(clicked()), this, SLOT(backImage()));
    connect(ui->PB_recortar, SIGNAL(clicked()), this, SLOT(cut()));
    connect(ui->PB_aceptar, SIGNAL(clicked()), this, SLOT(Save()));
    connect(ui->PB_salir, SIGNAL(clicked()), this, SLOT(close()));
}

Photoedit::~Photoedit()
{
    delete ui;
    delete mPainter;
    delete mImage;
    delete mImagePrev;
}

void Photoedit::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.drawImage(offset.x(), offset.y(), *mImage);
    ev->accept();
}

void Photoedit::mousePressEvent(QMouseEvent *ev)
{
    mEnabled = true;
    mBegin = ev->pos();
    //Corrijo el offset
    checkOffset(mBegin);
    ev->accept();
}

void Photoedit::mouseMoveEvent(QMouseEvent *ev)
{
    if(!mEnabled){
        ev->accept();
        return;
    }
    cleanWindow();
    mPainter->setPen(*pen);
    mEnd = ev->pos();
    checkOffset(mEnd);
    checkEndPoint(mEnd);
    mPainter->drawRect(mBegin.x(),mBegin.y(),mEnd.x()-mBegin.x(),mEnd.y()-mBegin.y());
    update();
    ev->accept();
}

void Photoedit::mouseReleaseEvent(QMouseEvent *ev)
{
    mEnabled = false;
    mPainter->setPen(*pen);
    mEnd = ev->pos();
    checkOffset(mEnd);
    checkEndPoint(mEnd);
    mPainter->drawRect(mBegin.x(),mBegin.y(),mEnd.x()-mBegin.x(),mEnd.y()-mBegin.y());
    update();
    ev->accept();
}

//Limpia el dibujo previo
void Photoedit::cleanWindow()
{
    delete mPainter;
    delete mImage;
    if(mCutImage == nullptr){
        mImage = new QImage(*pathImage);
    }
    else{
        mImage = new QImage(*mCutImage);
    }
    mPainter = new QPainter(mImage);
}

//Chequea el tamaño de la ventana
// para evitar dibujar por fuera
void Photoedit::checkEndPoint(QPoint &end)
{
    QSize sizeWindow(mImage->size());
    if(end.x() > sizeWindow.width()){
        end.setX(sizeWindow.width());
    }
    if(end.y() > sizeWindow.height()){
        end.setY(sizeWindow.height());
    }
    if(end.x() < 0){
        end.setX(0);
    }
    if(end.y() < 0){
        end.setY(0);
    }
}

void Photoedit::checkOffset(QPoint &point)
{
    point.setX(point.x() - offset.x());
    point.setY(point.y() - offset.y());
}

void Photoedit::refreshOffset()
{
    // Centro la imagen
    offset.setX((this->size().width()/2)-(mImage->width()/2));    // Tamaño ventana/2 - tamaño imagen/2
    offset.setY(((this->size().height()/2)-(mImage->height()/2))+(OFFSETY/2));    // Tamaño ventana/2 - tamaño imagen/2
}

void Photoedit::Save()
{

}

void Photoedit::cut()
{
    int xi, yi, xf, yf;

    if(mBegin.x() > mEnd.x()){
        xi = mEnd.x();
        xf = mBegin.x()-mEnd.x();
    }
    else{
        xi = mBegin.x();
        xf = mEnd.x()-mBegin.x();
    }

    if(mBegin.y() > mEnd.y()){
        yi = mEnd.y();
        yf = mBegin.y()-mEnd.y();
    }
    else{
        yi = mBegin.y();
        yf = mEnd.y()-mBegin.y();
    }

    if(mCutImage == nullptr)
        mImagePrev = new QImage(*pathImage);
    else
        mImagePrev = new QImage(*mCutImage);
    mCutImage = new QImage(mImage->copy(xi,yi,xf,yf));
    delete mPainter;
    delete mImage;
    mImage = new QImage(*mCutImage);
    mPainter = new QPainter(mImage);

    refreshOffset();
    update();
}

void Photoedit::backImage()
{
    if(mImagePrev == nullptr)
        return;
    delete mPainter;
    delete mImage;
    delete mCutImage;
    mImage = new QImage(*mImagePrev);
    mCutImage = new QImage(*mImagePrev);
    mPainter = new QPainter(mImage);

    refreshOffset();
    update();
}
