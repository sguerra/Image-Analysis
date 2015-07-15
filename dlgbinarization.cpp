#include "dlgbinarization.h"
#include "ui_dlgbinarization.h"

dlgBinarization::dlgBinarization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgBinarization)
{
    ui->setupUi(this);

    this->threshold = 0;

    connect(ui->sldrThreshold, SIGNAL(valueChanged(int)), this, SLOT(sldrThresholdChanged(int)));
    connect(ui->btnApply, SIGNAL(clicked(bool)), this, SLOT(btnApplyClicked(bool)));
    connect(ui->btnOtsu, SIGNAL(clicked(bool)), this, SLOT(btnOtsuClicked(bool)));
}

dlgBinarization::~dlgBinarization()
{
    delete ui;
}

void dlgBinarization::setLblThreshold(){
    QString format = QString::number(this->threshold);
    format.prepend("t = ");

    ui->lblThreshold->setText(format);
}

void dlgBinarization::setImage(dlgImage* imageDlg)
{
    if(imageDlg == NULL)
        return;

    this->imageDlg = imageDlg;
}

// Private Slots

void dlgBinarization::sldrThresholdChanged(int value){
   this->threshold = value;
   this->setLblThreshold();
}

void dlgBinarization::btnApplyClicked(bool checked){

    if(this->imageDlg == NULL)
        return;

    QImage image = this->imageDlg->getImage();
    this->imageProcessor.setImage(image);

    image = this->imageProcessor.binarize(this->threshold);
    this->imageDlg->setImage(image);
}

void dlgBinarization::btnOtsuClicked(bool checked){

    if(this->imageDlg == NULL)
        return;

    QImage image = this->imageDlg->getImage();
    this->imageProcessor.setImage(image);

    int threshold = this->imageProcessor.getOtsuThreshold();
    ui->sldrThreshold->setValue(threshold);
}

// Events

void dlgBinarization::closeEvent(QCloseEvent * e){
    e->ignore();
}
