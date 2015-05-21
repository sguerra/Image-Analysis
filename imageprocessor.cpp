#include "imageprocessor.h"
#include <QColor>

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





