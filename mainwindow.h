#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include "mymdiarea.h"
#include "imageprocessor.h"
#include "dlgimage.h"
#include "dlghistogram.h"
#include "dlgbinarization.h"

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
    void show_binarization();

    void subwindow_changed(QMdiSubWindow* window);

private:
    Ui::MainWindow *ui;
    MyMdiArea mdiArea;

    ImageProcessor imageProcessor;
    dlgHistogram* histogramDlg;
    dlgBinarization* binarizationDlg;

    void update_histogram();
    void update_binarization();

};

#endif // MAINWINDOW_H
