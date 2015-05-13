#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>

class ImageProcessor
{

public:
    ImageProcessor();

    QImage grayScale(QImage image);

};

#endif // IMAGEPROCESSOR_H
