#include "dlgbinarization.h"
#include "ui_dlgbinarization.h"

dlgBinarization::dlgBinarization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgBinarization)
{
    ui->setupUi(this);

    this->t = 0;
    connect(ui->sldrT, SIGNAL(valueChanged(int)), this, SLOT(sldrChanged(int)));
}

dlgBinarization::~dlgBinarization()
{
    delete ui;
}

void dlgBinarization::setLblT(){
    QString format = QString::number(this->t);
    format.prepend("t = ");

    ui->lblT->setText(format);
}

void dlgBinarization::setImage(dlgImage* imageDlg)
{
    if(imageDlg == NULL)
        return;

    this->imageDlg = imageDlg;
}

void dlgBinarization::sldrChanged(int value){
   this->t = value;
   this->setLblT();
}

void dlgBinarization::closeEvent(QCloseEvent * e){
    e->ignore();
}
