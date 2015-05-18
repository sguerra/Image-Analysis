#include "mymdiarea.h"
#include <QWidget>

MyMdiArea::MyMdiArea(): QMdiArea()
{
    //connect(this, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(subWindowChanged(QMdiSubWindow*)));
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


void MyMdiArea::setHistogram(dlgHistogram *histogramDlg){
    this->histogramDlg = histogramDlg;
}

// Private Slots

void MyMdiArea::subWindowChanged(QMdiSubWindow* window){
    dlgImage* imageDlg = this->getSelectedWindow();
    this->histogramDlg->setImage(imageDlg);
}

