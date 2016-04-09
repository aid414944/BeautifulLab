#include <iostream>

#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BeautifulLabGLWidget.h"
#include "Log.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pBeautifulLabGLWidget = new BeautifulLabGLWidget();
    ui->verticalLayout->addWidget(pBeautifulLabGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/aid", tr("Images (*.png *.xpm *.jpg)"));
    if (!fileName.isEmpty()){
        pBeautifulLabGLWidget->loadImage(fileName);
    }
}
