#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>

class ImageProcessor
{

private:
    QImage image;
    QVector<double> histChannel(QImage image, QColor color);

public:
    ImageProcessor();
    void setImage(QImage image);

    QImage grayScale();

    QVector<double> histRed();
    QVector<double> histGreen();
    QVector<double> histBlue();
    QVector<double> histGray();

};

#endif // IMAGEPROCESSOR_H
