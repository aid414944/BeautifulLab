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

private:
    Ui::MainWindow *ui;


private:
    BeautifulLabGLWidget * pBeautifulLabGLWidget;

};

#endif // MAINWINDOW_H
