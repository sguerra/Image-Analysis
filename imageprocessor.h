#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>
#include <QPair>
#include "moment.h"

class ImageProcessor
{

private:
    QImage image;
    QVector<double> histChannel(QImage image, QColor color);
    void adjustImageChannel(QVector<double> transform, QColor color);
    void adjustChannel(QColor color, int Xmax, int Xmin);

public:
    ImageProcessor();
    void setImage(QImage image);
    QImage getImage();

    QImage grayScale();
    QImage binarize(int t);
    int getOtsuThreshold();

    QVector< QPair<double, double> > getOnes();
    QVector<Moment> geoMoments();

    QVector<double> histRed();
    QVector<double> histGreen();
    QVector<double> histBlue();
    QVector<double> histGray();

    void adjustRed(int Xmax, int Xmin);
    void adjustGreen(int Xmax, int Xmin);
    void adjustBlue(int Xmax, int Xmin);
    void adjustGray(int Xmax, int Xmin);

};

#endif // IMAGEPROCESSOR_H
