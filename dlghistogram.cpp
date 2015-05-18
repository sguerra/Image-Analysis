#include "dlghistogram.h"
#include "ui_dlghistogram.h"

dlgHistogram::dlgHistogram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgHistogram)
{
    ui->setupUi(this);

    connect(ui->chkRed, SIGNAL(stateChanged(int)), this, SLOT(chksChanged(int)));
    connect(ui->chkGreen, SIGNAL(stateChanged(int)), this, SLOT(chksChanged(int)));
    connect(ui->chkBlue, SIGNAL(stateChanged(int)), this, SLOT(chksChanged(int)));
    connect(ui->chkGray, SIGNAL(stateChanged(int)), this, SLOT(chksChanged(int)));
}

dlgHistogram::~dlgHistogram()
{
    delete ui;
}

// Public Methods

void dlgHistogram::setImage(dlgImage* imageDlg)
{
    this->imageDlg = imageDlg;
    this->drawHistograms();
}

void dlgHistogram::drawHistograms(){

    if(this->imageDlg == NULL)
        return;

    QImage image = this->imageDlg->getImage();

    QVector<double> histRed = this->imageProcessor.histRed(image);
    QVector<double> histGreen = this->imageProcessor.histGreen(image);
    QVector<double> histBlue = this->imageProcessor.histBlue(image);
    QVector<double> histGray = this->imageProcessor.histGray(image);

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

// Events

 void dlgHistogram::chksChanged(int state){
    this->drawHistograms();
 }

void dlgHistogram::closeEvent(QCloseEvent * e){
    e->ignore();
}
