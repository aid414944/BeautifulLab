#include <iostream>

#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BeautifulLabGLWidget.h"
#include "Log.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    imageWidth(0),
    imageHeight(0)
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
        QImage image(fileName);
        imageWidth = image.width();
        imageHeight = image.height();
        pBeautifulLabGLWidget->loadImage(fileName); // TODO
        on_radius_slider_valueChanged(0);
        ui->radius_slider->setSliderPosition(0);
        on_strength_slider_valueChanged(0);
        ui->strength_slider->setSliderPosition(0);
    }
}

void MainWindow::on_strength_slider_valueChanged(int value)
{
    float strength = value/(float)ui->strength_slider->maximum();
    pBeautifulLabGLWidget->setBeautifulStrength(strength);
    ui->label_strength->setText(QString::number(strength));
    pBeautifulLabGLWidget->updateGL();
}

void MainWindow::on_radius_slider_valueChanged(int value)
{
    float a = value/(float)ui->radius_slider->maximum();
    int radius;
    if (imageWidth > imageHeight){
        radius = imageHeight*a;
    }else{
        radius = imageWidth*a;
    }
    pBeautifulLabGLWidget->setSamplingRadius(radius);
    ui->label_radius->setText(QString::number(radius));
    pBeautifulLabGLWidget->updateGL();
}
