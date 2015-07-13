#include "dlgbinarization.h"
#include "ui_dlgbinarization.h"

dlgBinarization::dlgBinarization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgBinarization)
{
    ui->setupUi(this);

    this->t = 0;

    connect(ui->sldrT, SIGNAL(valueChanged(int)), this, SLOT(sldrTChanged(int)));
    connect(ui->btnApply, SIGNAL(clicked(bool)), this, SLOT(btnApplyClicked(bool)));
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

// Private Slots

void dlgBinarization::sldrTChanged(int value){
   this->t = value;
   this->setLblT();
}

void dlgBinarization::btnApplyClicked(bool checked){

    if(this->imageDlg == NULL)
        return;

    QImage image = this->imageDlg->getImage();
    this->imageProcessor.setImage(image);

    image = this->imageProcessor.binarize(this->t);
    this->imageDlg->setImage(image);
}

// Events

void dlgBinarization::closeEvent(QCloseEvent * e){
    e->ignore();
}
