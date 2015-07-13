#include "dlgbinarization.h"
#include "ui_dlgbinarization.h"

dlgBinarization::dlgBinarization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgBinarization)
{
    ui->setupUi(this);
}

dlgBinarization::~dlgBinarization()
{
    delete ui;
}
