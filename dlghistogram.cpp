#include "dlghistogram.h"
#include "ui_dlghistogram.h"

dlgHistogram::dlgHistogram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgHistogram)
{
    ui->setupUi(this);
}

dlgHistogram::~dlgHistogram()
{
    delete ui;
}


// Events

void dlgHistogram::closeEvent(QCloseEvent * e){
    e->ignore();
    this->parentWidget()->hide();
}
