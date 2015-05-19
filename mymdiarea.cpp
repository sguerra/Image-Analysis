#include "mymdiarea.h"
#include <QWidget>

MyMdiArea::MyMdiArea(): QMdiArea()
{
}

// Public Methods

dlgImage* MyMdiArea::getSelectedWindow(){

    QMdiSubWindow* subWindow  = this->activeSubWindow();

    if(subWindow == 0)
        return NULL;

    QWidget* widget = subWindow->widget();
    dlgImage* selectedWindow = dynamic_cast<dlgImage*>(widget);

    if(selectedWindow==NULL)
        return selectedImageDlg;

    selectedImageDlg = selectedWindow;
    return selectedImageDlg;
}
