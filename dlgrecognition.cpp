#include "dlgrecognition.h"
#include "ui_dlgrecognition.h"

// Constructor

dlgRecognition::dlgRecognition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgRecognition)
{
    ui->setupUi(this);
}

dlgRecognition::~dlgRecognition()
{
    delete ui;
}

// Private Methods

void dlgRecognition::setImage(dlgImage* imageDlg)
{
    if(imageDlg == NULL)
        return;

    this->imageDlg = imageDlg;
}

// Protected Methods

void dlgRecognition::closeEvent(QCloseEvent* e){
    e->ignore();
}

