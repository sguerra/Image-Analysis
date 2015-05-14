#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "imageprocessor.h"
#include "dlgimage.h"
#include "dlghistogram.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();
    void save_as();

    void gray_scale();
    void show_histogram();

private:
    Ui::MainWindow *ui;
    QMdiArea mdiArea;

    ImageProcessor imageProcessor;
    dlgHistogram* histogramDlg;

    dlgImage* selectedImageDlg;
    dlgImage* getSelectedWindow();

};

#endif // MAINWINDOW_H
