#ifndef DLGBINARIZATION_H
#define DLGBINARIZATION_H

#include <QDialog>

namespace Ui {
class dlgBinarization;
}

class dlgBinarization : public QDialog
{
    Q_OBJECT

public:
    explicit dlgBinarization(QWidget *parent = 0);
    ~dlgBinarization();

private:
    Ui::dlgBinarization *ui;
};

#endif // DLGBINARIZATION_H
