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

private:
    dlgImage* imageDlg;

    Ui::dlgHistogram *ui;
    ImageProcessor imageProcessor;

    void drawHistograms();
    void setLblRange();

    int minValue;
    int maxValue;

public:
    explicit dlgHistogram(QWidget *parent = 0);
    ~dlgHistogram();

    void setImage(dlgImage* imageDlg);

private slots:
    void chksChanged(int state);
    void sldrMinChanged(int value);
    void sldrMaxChanged(int value);

protected:
    void closeEvent(QCloseEvent * e);

};

#endif // DLGHISTOGRAM_H
