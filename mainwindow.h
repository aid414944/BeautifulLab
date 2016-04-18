#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BeautifulLabGLWidget.h"

using namespace std;

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
    void on_actionOpen_file_triggered();
    void on_strength_slider_valueChanged(int value);
    void on_radius_slider_valueChanged(int value);

private:
    Ui::MainWindow *ui;


private:
    BeautifulLabGLWidget * pBeautifulLabGLWidget;
    int imageWidth;
    int imageHeight;

};

#endif // MAINWINDOW_H
