#include "dlghistogram.h"
#include "ui_dlghistogram.h"

dlgHistogram::dlgHistogram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgHistogram)
{
    ui->setupUi(this);

    this->minValue = 0;
    this->maxValue = 255;

    connect(ui->chkRed, SIGNAL(stateChanged(int)), this, SLOT(chksChanged(int)));
    connect(ui->chkGreen, SIGNAL(stateChanged(int)), this, SLOT(chksChanged(int)));
    connect(ui->chkBlue, SIGNAL(stateChanged(int)), this, SLOT(chksChanged(int)));
    connect(ui->chkGray, SIGNAL(stateChanged(int)), this, SLOT(chksChanged(int)));
    connect(ui->sldrMin, SIGNAL(valueChanged(int)), this, SLOT(sldrMinChanged(int)));
    connect(ui->sldrMax, SIGNAL(valueChanged(int)), this, SLOT(sldrMaxChanged(int)));
}

dlgHistogram::~dlgHistogram()
{
    delete ui;
}

// Public Methods

void dlgHistogram::setImage(dlgImage* imageDlg)
{
    if(imageDlg == NULL)
        return;

    this->imageDlg = imageDlg;
    this->drawHistograms();
}

void dlgHistogram::drawHistograms(){

    if(this->imageDlg == NULL)
        return;

    QImage image = this->imageDlg->getImage();
    this->imageProcessor.setImage(image);

    QVector<double> histRed = this->imageProcessor.histRed();
    QVector<double> histGreen = this->imageProcessor.histGreen();
    QVector<double> histBlue = this->imageProcessor.histBlue();
    QVector<double> histGray = this->imageProcessor.histGray();

    QVector<double> x(255);
    for (int i=0; i< x.length(); ++i){
      x[i] = i;
    }

    int maxY = 0;

    for (int i=0; i< histRed.length() ; i++){
        if(histRed[i] > maxY){
            maxY = histRed[i];
        }
    }
    for (int i=0; i< histGreen.length() ; i++){
        if(histGreen[i] > maxY){
            maxY = histGreen[i];
        }
    }
    for (int i=0; i< histBlue.length() ; i++){
        if(histBlue[i] > maxY){
            maxY = histBlue[i];
        }
    }
    for (int i=0; i< histGray.length() ; i++){
        if(histGray[i] > maxY){
            maxY = histGray[i];
        }
    }

    QCustomPlot* axis = ui->pltHistogram;

    axis->addGraph();
    axis->graph(0)->setData(x, histRed);
    axis->graph(0)->setPen(QPen(Qt::red));
    axis->graph(0)->setBrush(QBrush(QColor(255, 0, 0, 50)));
    axis->graph(0)->setVisible(ui->chkRed->isChecked());

    axis->addGraph();
    axis->graph(1)->setData(x, histGreen);
    axis->graph(1)->setPen(QPen(Qt::green));
    axis->graph(1)->setBrush(QBrush(QColor(0, 255, 0, 50)));
    axis->graph(1)->setVisible(ui->chkGreen->isChecked());

    axis->addGraph();
    axis->graph(2)->setData(x, histBlue);
    axis->graph(2)->setPen(QPen(Qt::blue));
    axis->graph(2)->setBrush(QBrush(QColor(0, 0, 255, 50)));
    axis->graph(2)->setVisible(ui->chkBlue->isChecked());

    axis->addGraph();
    axis->graph(3)->setData(x, histGray);
    axis->graph(3)->setPen(QPen(Qt::black));
    axis->graph(3)->setBrush(QBrush(QColor(0, 0, 0, 50)));
    axis->graph(3)->setVisible(ui->chkGray->isChecked());

    axis->xAxis->setRange(0, 255);
    axis->yAxis->setRange(0, maxY);
    axis->replot();
}

void dlgHistogram::setLblRange()
{
    QString format = QString::number(this->minValue);
    format.append(" - ");
    format.append(QString::number(this->maxValue));

    ui->lblRange->setText(format);
}

// Events

 void dlgHistogram::chksChanged(int state){
    this->drawHistograms();
 }

 void dlgHistogram::sldrMinChanged(int value){
    this->minValue = value;
     ui->sldrMax->setMinimum(value+1);
    this->setLblRange();
 }

 void dlgHistogram::sldrMaxChanged(int value){
    this->maxValue = value;
     ui->sldrMin->setMaximum(value-1);
     this->setLblRange();
 }

void dlgHistogram::closeEvent(QCloseEvent * e){
    e->ignore();
}
