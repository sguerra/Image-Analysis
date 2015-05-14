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

// Public Methods

void dlgHistogram::setImage(dlgImage* imageDlg)
{
    if(imageDlg == NULL)
        return;

    QImage image = imageDlg->getImage();

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

    axis->addGraph();
    axis->graph(1)->setData(x, histGreen);
    axis->graph(1)->setPen(QPen(Qt::green));
    axis->graph(1)->setBrush(QBrush(QColor(0, 255, 0, 50)));

    axis->addGraph();
    axis->graph(2)->setData(x, histBlue);
    axis->graph(2)->setPen(QPen(Qt::blue));
    axis->graph(2)->setBrush(QBrush(QColor(0, 0, 255, 50)));

    axis->addGraph();
    axis->graph(3)->setData(x, histGray);
    axis->graph(3)->setPen(QPen(Qt::black));
    axis->graph(3)->setBrush(QBrush(QColor(0, 0, 0, 50)));

    axis->xAxis->setRange(0, 255);
    axis->yAxis->setRange(0, maxY);
    axis->replot();
}

// Events

void dlgHistogram::closeEvent(QCloseEvent * e){
    e->ignore();
}
