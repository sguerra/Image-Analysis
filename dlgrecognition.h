#ifndef DLGRECOGNITION_H
#define DLGRECOGNITION_H

#include <QDialog>
#include <QCloseEvent>
#include "dlgimage.h"
#include "imageprocessor.h"

namespace Ui {
class dlgRecognition;
}

class dlgRecognition : public QDialog
{
    Q_OBJECT

private:
    dlgImage* imageDlg;
    ImageProcessor imageProcessor;

    Ui::dlgRecognition *ui;

public:
    explicit dlgRecognition(QWidget *parent = 0);
    ~dlgRecognition();

    void setImage(dlgImage* imageDlg);

protected:
    void closeEvent(QCloseEvent * e);

};

#endif // DLGRECOGNITION_H
