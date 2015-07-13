#ifndef DLGBINARIZATION_H
#define DLGBINARIZATION_H

#include <QDialog>
#include <QCloseEvent>
#include "dlgimage.h"
#include "imageprocessor.h"

namespace Ui {
class dlgBinarization;
}

class dlgBinarization : public QDialog
{
    Q_OBJECT

private:
    dlgImage* imageDlg;
    ImageProcessor imageProcessor;

    Ui::dlgBinarization *ui;
    int t;

    void setLblT();

public:
    explicit dlgBinarization(QWidget *parent = 0);
    ~dlgBinarization();

    void setImage(dlgImage* imageDlg);

private slots:
    void sldrTChanged(int value);
    void btnApplyClicked(bool checked);

protected:
    void closeEvent(QCloseEvent * e);

};

#endif // DLGBINARIZATION_H
