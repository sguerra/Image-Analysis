#include "dlgrecognition.h"
#include "ui_dlgrecognition.h"

// Constructor

dlgRecognition::dlgRecognition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgRecognition)
{
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(btnAddClicked(bool)));
    connect(ui->btnRecognize, SIGNAL(clicked(bool)), this, SLOT(btnRecognizeClicked(bool)));

    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/A0.jpg"), "JPG"), QString("A"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/A1.jpg"), "JPG"), QString("A"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/A2.jpg"), "JPG"), QString("A"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/A3.jpg"), "JPG"), QString("A"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/B0.jpg"), "JPG"), QString("B"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/B1.jpg"), "JPG"), QString("B"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/B2.jpg"), "JPG"), QString("B"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/B3.jpg"), "JPG"), QString("B"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/C0.jpg"), "JPG"), QString("C"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/C1.jpg"), "JPG"), QString("C"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/C2.jpg"), "JPG"), QString("C"));
    this->addClassItem(QImage(QString("/Users/Sergije/Pictures/Letters/training/C3.jpg"), "JPG"), QString("C"));
}

dlgRecognition::~dlgRecognition()
{
    delete ui;
}

// Private Methods

void dlgRecognition::addClassItem(QImage image, QString className){

    this->imageProcessor.setImage(image);
    image =  this->imageProcessor.binarize( this->imageProcessor.getOtsuThreshold() );

    this->imageProcessor.setImage(image);
    QVector<double> vector = this->imageProcessor.huMoments();

    ClassItem classItem(vector, className);
    this->database.append(classItem);
    ui->txtClassName->clear();
}


// Public Methods

void dlgRecognition::setImage(dlgImage* imageDlg)
{
    if(imageDlg == NULL)
        return;

    this->imageDlg = imageDlg;
}


// Protected Methods

void dlgRecognition::btnAddClicked(bool checked){

    if(this->imageDlg == NULL)
        return;

    QImage image = this->imageDlg->getImage();
    QString className = ui->txtClassName->text();

    if(className.isEmpty()){
        return;
    }

    this->addClassItem(image, className);
}

void dlgRecognition::btnRecognizeClicked(bool cheked){

    if(this->imageDlg == NULL)
        return;

    QImage image = this->imageDlg->getImage();

    this->imageProcessor.setImage(image);
    image =  this->imageProcessor.binarize( this->imageProcessor.getOtsuThreshold() );

    this->imageProcessor.setImage(image);
    QVector<double> vector = this->imageProcessor.huMoments();

    int k = 1;

    QVector< QPair<ClassItem, double> > neighbors;

    for(int i = 0; i < this->database.size(); i++){
        neighbors.append( QPair<ClassItem, double>(this->database[i], this->database[i].getDistance(vector, 0)));
    }

    for(int i = 0; i < neighbors.size(); i++){
        for(int j = 1; j < neighbors.size(); j++){
            QPair<ClassItem, double> aux = neighbors[j];

            if(neighbors[j - 1].second > neighbors[j].second){
                neighbors[j] = neighbors[j - 1];
                neighbors[j - 1] = aux;
            }
        }
    }

    ui->txtResult->setText(neighbors[0].first.getClassName());
}

void dlgRecognition::closeEvent(QCloseEvent* e){
    e->ignore();
}

