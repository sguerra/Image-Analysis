#include "imageprocessor.h"
#include <QColor>

ImageProcessor::ImageProcessor()
{

}

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

