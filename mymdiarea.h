#ifndef MYMDIAREA_H
#define MYMDIAREA_H

#include <QMdiArea>
#include <QMdiSubWindow>
#include "dlghistogram.h"
#include "dlgimage.h"

class MyMdiArea : public QMdiArea
{
private:
    dlgImage* selectedImageDlg;

public:
    MyMdiArea();

    dlgHistogram* histogramDlg;
    void setHistogram(dlgHistogram* histogramDlg);

    dlgImage* getSelectedWindow();

private slots:
    void subWindowChanged(QMdiSubWindow* window);

};

#endif // MYMDIAREA_H
