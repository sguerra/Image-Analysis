#ifndef DLGHISTOGRAM_H
#define DLGHISTOGRAM_H

#include <QDialog>
#include <QCloseEvent>
#include "dlgimage.h"
#include "imageprocessor.h"

namespace Ui {
class dlgHistogram;
}

class dlgHistogram : public QDialog
{
    Q_OBJECT

public:
    explicit dlgHistogram(QWidget *parent = 0);
    ~dlgHistogram();

    void setImage(dlgImage* imageDlg);

private:
    Ui::dlgHistogram *ui;
    ImageProcessor imageProcessor;

protected:
    void closeEvent(QCloseEvent * e);

};

#endif // DLGHISTOGRAM_H
