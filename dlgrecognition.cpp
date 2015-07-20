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

    // get Hu Moments vector
    QImage image = this->imageDlg->getImage();

    this->imageProcessor.setImage(image);
    image =  this->imageProcessor.binarize( this->imageProcessor.getOtsuThreshold() );

    this->imageProcessor.setImage(image);
    QVector<double> vector = this->imageProcessor.huMoments();

    // Sets Neighborhood
    QVector< QPair<ClassItem, double> > neighbors;

    int metric = ui->rdbAbsolute->isChecked() ? METRIC_ABSOLUTE : ui->rdbEuclidean->isChecked() ? METRIC_EUCLIDEAN : METRIC_INFINITE;

    for(int i = 0; i < this->database.size(); i++){
        neighbors.append( QPair<ClassItem, double>(this->database[i], this->database[i].getDistance(vector, metric)));
    }

    // Orders Neighborhood
    for(int i = 0; i < neighbors.size(); i++){
        for(int j = 1; j < neighbors.size(); j++){
            QPair<ClassItem, double> aux = neighbors[j];

            if(neighbors[j - 1].second > neighbors[j].second){
                neighbors[j] = neighbors[j - 1];
                neighbors[j - 1] = aux;
            }
        }
    }

    // Finds K Nearest Neighbor
    int k = ui->txtK->text().toInt(0, 10);

    if(k==0){
        return;
    }

    QMap<QString, int> frequency;
    QString result("NONE");

    for(int i=0; i < k;i++){
        QString classname = neighbors[i].first.getClassName();

        if(frequency.contains(classname)){
            frequency[classname]++;
        }
        else{
            frequency.insert(classname, 1);
        }
    }

    int max_frequency = 0;

    QMap<QString, int>::const_iterator iterator = frequency.constBegin();
    while (iterator != frequency.constEnd()) {

        int value = iterator.value();
        QString classname = iterator.key();

        if(max_frequency < value){
            max_frequency = value;
            result = classname;
        }

        iterator++;
    }

    ui->txtResult->setText(result);
}

void dlgRecognition::closeEvent(QCloseEvent* e){
    e->ignore();
}

