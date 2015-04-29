#include "mylabel.h"
#include <QMouseEvent>
#include <QImage>
#include <QPixmap>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    statusBar=NULL;
}

MyLabel::~MyLabel()
{

}

void MyLabel::setStatusBar(QStatusBar *sb) {
    statusBar=sb;
}

void MyLabel::mouseMoveEvent(QMouseEvent * ev) {

    int x=ev->x();
    int y=ev->y();

    QRgb pixel=pixmap()->toImage().pixel(x,y);

    int r=qRed(pixel);
    int g=qGreen(pixel);
    int b=qBlue(pixel);
    QString text;

    text.sprintf("[X=%d, Y=%d] R=%d G=%d B=%d",x,y,r,g,b);

    statusBar->showMessage(text);



}








