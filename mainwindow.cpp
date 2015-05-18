#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMdiSubWindow>
#include "dlgimage.cpp"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(save_as()));
    connect(ui->actionGrayscale, SIGNAL(triggered()), this, SLOT(gray_scale()));
    connect(ui->actionHistogram, SIGNAL(triggered()), this, SLOT(show_histogram()));

    //Window
    QDesktopWidget desktop;

    int width = geometry().width();
    int height = geometry().height();

    int screenWidth = desktop.screen()->width();
    int screenHeight = desktop.screen()->height();

    setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);
    setCentralWidget(&mdiArea);

    // Histogram dialog
    histogramDlg = new dlgHistogram(&mdiArea);
    mdiArea.setHistogram(histogramDlg);
    mdiArea.addSubWindow(histogramDlg);

    histogramDlg->parentWidget()->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Private Methods

void MainWindow::open() {

    QString fileName;

    fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));

    if(fileName == NULL)
        return;

    ui->statusBar->showMessage(fileName);

    dlgImage *w;
    w=new dlgImage(&mdiArea);
    w->setFileName(fileName);
    w->setStatusBar(ui->statusBar);

    mdiArea.addSubWindow(w);
    w->show();

    this->update_histogram();
}


void MainWindow::save_as() {
    QString fileName;

    fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));

    ui->statusBar->showMessage(fileName);
    //ui->label->pixmap()->save(fileName);
}

void MainWindow::gray_scale() {

    QWidget* selectedWindow = this->mdiArea.getSelectedWindow();

    if(selectedWindow==NULL)
        return;

    dlgImage* dialog = (dlgImage*)selectedWindow;

    QImage image = dialog->getImage();
    QImage gray = imageProcessor.grayScale(image);

    dialog->setImage(gray);
}

void MainWindow::show_histogram()
{
    QWidget* parent = histogramDlg->parentWidget();
    bool actionChecked = ui->actionHistogram->isChecked();

    if(actionChecked){
        parent->show();
        this->update_histogram();
    }else{
        parent->hide();
    }
}

void MainWindow::update_histogram()
{
    dlgImage* selected = this->mdiArea.getSelectedWindow();
    histogramDlg->setImage(selected);
}








