#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "imageprocessor.h"

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

private:
    Ui::MainWindow *ui;
    QMdiArea mdiArea;

    QWidget* getSelectedWindow();

    ImageProcessor imageProcessor;
};

#endif // MAINWINDOW_H
