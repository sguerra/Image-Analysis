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

    dlgImage* getSelectedWindow();

};

#endif // MYMDIAREA_H
