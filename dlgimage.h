#ifndef DLGIMAGE_H
#define DLGIMAGE_H

#include <QDialog>
#include "mylabel.h"
#include <QStatusBar>

namespace Ui {
class dlgImage;
}

class dlgImage : public QDialog
{
    Q_OBJECT

public:
    explicit dlgImage(QWidget *parent = 0);
    ~dlgImage();

    void setFileName(QString file);
    void setStatusBar(QStatusBar *sb);

private:
    Ui::dlgImage *ui;

};

#endif // DLGIMAGE_H
