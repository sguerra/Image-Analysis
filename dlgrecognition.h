#ifndef DLGRECOGNITION_H
#define DLGRECOGNITION_H

#include <QDialog>
#include <QCloseEvent>
#include <QPair>
#include <QMap>
#include "dlgimage.h"
#include "imageprocessor.h"
#include "classitem.h"

namespace Ui {
class dlgRecognition;
}

class dlgRecognition : public QDialog
{
    Q_OBJECT

private:
    dlgImage* imageDlg;
    ImageProcessor imageProcessor;
    QVector<ClassItem> database;

    Ui::dlgRecognition *ui;

    void addClassItem(QImage image, QString className);

public:
    explicit dlgRecognition(QWidget *parent = 0);
    ~dlgRecognition();

    void setImage(dlgImage* imageDlg);

private slots:
    void btnAddClicked(bool cheked);
    void btnRecognizeClicked(bool cheked);

protected:
    void closeEvent(QCloseEvent * e);

};

#endif // DLGRECOGNITION_H
