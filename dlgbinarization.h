#ifndef DLGBINARIZATION_H
#define DLGBINARIZATION_H

#include <QDialog>
#include <QCloseEvent>
#include "dlgimage.h"

namespace Ui {
class dlgBinarization;
}

class dlgBinarization : public QDialog
{
    Q_OBJECT

private:
    dlgImage* imageDlg;

    Ui::dlgBinarization *ui;
    int t;

    void setLblT();

public:
    explicit dlgBinarization(QWidget *parent = 0);
    ~dlgBinarization();

    void setImage(dlgImage* imageDlg);

private slots:
    void sldrChanged(int value);

protected:
    void closeEvent(QCloseEvent * e);

};

#endif // DLGBINARIZATION_H
