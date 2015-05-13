#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMdiSubWindow>
#include "dlgimage.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(save_as()));
    connect(ui->actionGrayscale, SIGNAL(triggered()), this, SLOT(gray_scale()));

    setCentralWidget(&mdiArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open() {
    //QPixmap pix;
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));

    if(fileName == NULL)
        return;

    //pix.load(fileName);
    //ui->label->setPixmap(pix);

    ui->statusBar->showMessage(fileName);

    dlgImage *w;
    w=new dlgImage(&mdiArea);
    w->setFileName(fileName);
    w->setStatusBar(ui->statusBar);

    mdiArea.addSubWindow(w);

    w->show();

}

void MainWindow::save_as() {
    QString fileName;

    fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));

    ui->statusBar->showMessage(fileName);
    //ui->label->pixmap()->save(fileName);
}

void MainWindow::gray_scale() {

    QWidget* selectedWindow = getSelectedWindow();

    if(selectedWindow==NULL)
        return;

    dlgImage* dialog = (dlgImage*)selectedWindow;

    QImage image = dialog->getImage();
    QImage gray = imageProcessor.grayScale(image);

    dialog->setImage(gray);
}

QWidget* MainWindow::getSelectedWindow(){

    QMdiSubWindow* subWindow  = mdiArea.activeSubWindow();

    if(subWindow == 0)
        return NULL;

    QWidget* widget = subWindow->widget();

    return widget;
}













