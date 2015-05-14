#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>

class ImageProcessor
{

private:

    QVector<double> histChannel(QImage image, QColor color);

public:
    ImageProcessor();

    QImage grayScale(QImage image);

    QVector<double> histRed(QImage image);
    QVector<double> histGreen(QImage image);
    QVector<double> histBlue(QImage image);
    QVector<double> histGray(QImage image);

};

#endif // IMAGEPROCESSOR_H
