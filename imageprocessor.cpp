#include "imageprocessor.h"
#include <QColor>
#include <QtMath>

const int ONE = 255;
const int ZERO = 0;

ImageProcessor::ImageProcessor()
{

}

// Private Methods

QVector<double> ImageProcessor::histChannel(QImage image, QColor color)
{
    QVector<double> histogram(256);

    int width = image.width();
    int height = image.height();

    for(int j = 0; j < height; j++)
    {
        QRgb* row = (QRgb*)image.scanLine(j);

        for(int i = 0; i < width; i++)
        {
            QRgb pixel = row[i];

            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            if(color == QColor(Qt::red))
                histogram[red] += 1;
            else if(color == QColor(Qt::green))
                histogram[green] += 1;
            else if(color == QColor(Qt::blue))
                histogram[blue] += 1;
        }
    }

    return histogram;
}

// Public Methods

void ImageProcessor::setImage(QImage image)
{
    this->image =  image;
}
QImage ImageProcessor::getImage(){
    return this->image;
}

QImage ImageProcessor::grayScale()
{
    int width = this->image.width();
    int height = this->image.height();

    QImage gray(width, height, QImage::Format_ARGB32);

    for(int j = 0; j < height; j++)
    {
        QRgb* row = (QRgb*)this->image.scanLine(j);

        for(int i = 0; i < width; i++)
        {
            QRgb pixel = row[i];

            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            double value = (0.299*red) + (0.587*green) + (0.14*blue);

           gray.setPixel(i, j, qRgb(value, value, value));
        }

    }

    return gray;
}
QImage ImageProcessor::binarize(int t)
{
    this->image = grayScale();

    int width = this->image.width();
    int height = this->image.height();

    QImage binarized(width, height, QImage::Format_ARGB32);

    for(int j = 0; j < height; j++)
    {
        QRgb* row = (QRgb*)this->image.scanLine(j);

        for(int i = 0; i < width; i++)
        {
            QRgb pixel = row[i];

            int gray = qRed(pixel);

            int value = gray < t ? 0 : 255;
            binarized.setPixel(i, j, qRgb(value, value, value));
        }
    }

    return binarized;
}
int ImageProcessor::getOtsuThreshold(){

    int threshold = 0;
    QVector<double> histogram = this->histGray();

    int width = this->image.width();
    int height = this->image.height();
    int size = width * height;

    // P1, P2, M1, M2, P1*P2*(M2-M1)^2
    QVector<double> p1(256);
    QVector<double> p2(256);
    QVector<double> m1(256);
    QVector<double> m2(256);

    QVector<double> p1_p2_m1_m2_2(256);

    double p1sum = 0;
    double p2sum = 0;
    double m1sum = 0;
    double m2sum = 0;

    for(int t = 0; t <= 255; t++){
        double value = histogram[t];
        p2sum += value;
        m2sum += t*value;
    }

    for(int t = 0; t <= 255; t++){

        double value = histogram[t];
        p1sum += value;
        p2sum -= value;

        p1[t] = p1sum/size;
        p2[t] = 1 - p1[t];

        m1sum += t*value;
        m2sum -= t*value;

        m1[t] = p1sum ? m1sum/p1sum : 0;
        m2[t] = p2sum ? m2sum/p2sum : 0;

        p1_p2_m1_m2_2[t] = p1[t] * p2[t] * qPow(m2[t] - m1[t], 2);
    }


    // MAX P1*P2*(M2-M1)^2
    double aux = 0;

    for(int t = 0; t <= 255; t++){

        threshold = t;

        if(t==0){
            aux = p1_p2_m1_m2_2[t];
            continue;
        }

        if(p1_p2_m1_m2_2[t] >= aux){
            aux = p1_p2_m1_m2_2[t];
            continue;
        }

        break;
    }

    return threshold;
}


// Hu Moments Methods

QVector< QPair<double, double> >  ImageProcessor::getOnes(){
    QVector< QPair<double, double> > ones;

    int width = this->image.width();
    int height = this->image.height();

    for(int j = 0; j < height; j++)
    {
        QRgb* row = (QRgb*)this->image.scanLine(j);

        for(int i = 0; i < width; i++)
        {
            QRgb pixel = row[i];
            int value = qRed(pixel);

            if(value==ONE){
                QPair<double, double> one(i, j);
                ones.push_back(one);
            }
        }
    }

    return ones;
}
QVector<Moment> ImageProcessor::geoMoments(){

    QVector<Moment> moments(10);

    moments[0].setOrder(0, 0);
    moments[1].setOrder(0, 1);
    moments[2].setOrder(1, 0);
    moments[3].setOrder(1, 1);
    moments[4].setOrder(2, 0);
    moments[5].setOrder(0, 2);
    moments[6].setOrder(2, 1);
    moments[7].setOrder(1, 2);
    moments[8].setOrder(3, 0);
    moments[9].setOrder(0, 3);

    QVector< QPair<double, double> > ones = this->getOnes();

    for(int m = 0;m<moments.size();m++){
        Moment moment = moments[m];

        double value = 0;

        for(int i; i < ones.size();i++){

            QPair<double, double> one = ones[i];
            double x = one.first;
            double y = one.second;

            value += qPow(x, moment.getP()) * qPow(y, moment.getQ());
        }

        moments[m].setValue(value);
    }

    return moments;
}
QVector<Moment> ImageProcessor::centralMoments(){

    QVector<Moment> geo_moments = this->geoMoments();
    QVector<Moment> moments = geo_moments;

    double m00 = geo_moments[0].getValue();
    double m01 = geo_moments[1].getValue();
    double m10 = geo_moments[2].getValue();

    // center
    double xc = m10/m00;
    double yc = m01/m00;

    QVector< QPair<double, double> > ones = this->getOnes();

    for(int m = 0;m<moments.size();m++){
        Moment moment = moments[m];
        double value = 0;

        for(int i; i < ones.size();i++){

            QPair<double, double> one = ones[i];
            double x = one.first;
            double y = one.second;

            value += qPow((x-xc), moment.getP()) * qPow((y-yc), moment.getQ());
        }

        moments[m].setValue(value);
    }

    return moments;
}

// Get Histogram Methods

QVector<double> ImageProcessor::histRed()
{
    return this->histChannel(this->image, QColor(Qt::red));
}
QVector<double> ImageProcessor::histGreen()
{
    return this->histChannel(this->image, QColor(Qt::green));
}
QVector<double> ImageProcessor::histBlue()
{
    return this->histChannel(this->image, QColor(Qt::blue));
}
QVector<double> ImageProcessor::histGray()
{
    return this->histChannel(this->grayScale(), QColor(Qt::red));
}

// Adjust Histogram Methods

void ImageProcessor::adjustImageChannel(QVector<double> transform, QColor color)
{
    int width = this->image.width();
    int height = this->image.height();

    for(int j = 0; j < height; j++)
    {
        QRgb* row = (QRgb*)this->image.scanLine(j);

        for(int i = 0; i < width; i++)
        {
            QRgb pixel = row[i];

            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            if(color==Qt::red){
                red = transform[red];
            } else if(color==Qt::green){
                green = transform[green];
            } else if(color==Qt::blue){
                blue = transform[blue];
            } else if(color==Qt::gray){
                red = transform[red];
                green = transform[green];
                blue = transform[blue];
            }

           this->image.setPixel(i, j, qRgb(red, green, blue));
        }

    }
}

void ImageProcessor::adjustChannel(QColor color, int Xmax, int Xmin)
{
        QVector<double> histogram;

        if(color == Qt::red)
            histogram = this->histRed();
        else if(color == Qt::green)
            histogram = this->histGreen();
        else if(color == Qt::blue)
            histogram = this->histBlue();
        else if(color == Qt::gray)
            histogram = this->histGray();

        int size = histogram.size();

        QVector<double> adjusted(size);
        QVector<double> transform(size);

       double xmax = 0;
       double xmin = 255;

       for(int i=0; i < size; i++)
       {
           double value = histogram.at(i);

           if(value == 0)
               continue;

           double x = i;

            if(x>xmax){
                xmax = x;
            }if(x<xmin){
                xmin = x;
            }
       }

       for(int i=0; i < size; i++)
       {
           double value = histogram.at(i);

           if(value == 0)
               continue;

           double x = i;

           int X = ((Xmax - Xmin)*(x - xmin)/(xmax - xmin)) + Xmin;// (xmax - xmin)/(x - xmin) = (Xmax - Xmin)/(X - Xmin)
           adjusted[X] = value;

           transform[i] = X;
       }

       this->adjustImageChannel(transform, color);
}

void ImageProcessor::adjustRed(int Xmax, int Xmin)
{
       this->adjustChannel(Qt::red, Xmax, Xmin);
}
void ImageProcessor::adjustGreen(int Xmax, int Xmin)
{
       this->adjustChannel(Qt::green, Xmax, Xmin);
}
void ImageProcessor::adjustBlue(int Xmax, int Xmin)
{
       this->adjustChannel(Qt::blue, Xmax, Xmin);
}
void ImageProcessor::adjustGray(int Xmax, int Xmin)
{
    this->adjustChannel(Qt::gray, Xmax, Xmin);
}





