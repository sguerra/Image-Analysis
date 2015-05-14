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

QImage ImageProcessor::grayScale(QImage image)
{
    int width = image.width();
    int height = image.height();

    QImage gray(width, height, QImage::Format_ARGB32);

    for(int j = 0; j < height; j++)
    {
        QRgb* row = (QRgb*)image.scanLine(j);

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


QVector<double> ImageProcessor::histRed(QImage image)
{
    return this->histChannel(image, QColor(Qt::red));
}
QVector<double> ImageProcessor::histGreen(QImage image)
{
    return this->histChannel(image, QColor(Qt::green));
}
QVector<double> ImageProcessor::histBlue(QImage image)
{
    return this->histChannel(image, QColor(Qt::blue));
}
QVector<double> ImageProcessor::histGray(QImage image)
{
    return this->histChannel(this->grayScale(image), QColor(Qt::red));
}
