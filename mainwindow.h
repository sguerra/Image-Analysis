#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include "mymdiarea.h"
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

    void subwindow_changed(QMdiSubWindow* window);

private:
    Ui::MainWindow *ui;
    MyMdiArea mdiArea;

    ImageProcessor imageProcessor;
    dlgHistogram* histogramDlg;

    void update_histogram();

};

#endif // MAINWINDOW_H
