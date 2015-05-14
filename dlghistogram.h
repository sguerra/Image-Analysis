#ifndef DLGHISTOGRAM_H
#define DLGHISTOGRAM_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class dlgHistogram;
}

class dlgHistogram : public QDialog
{
    Q_OBJECT

public:
    explicit dlgHistogram(QWidget *parent = 0);
    ~dlgHistogram();

private:
    Ui::dlgHistogram *ui;

protected:
    void closeEvent(QCloseEvent * e);

};

#endif // DLGHISTOGRAM_H
