#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->signalDrop->addItems({"Sine","Square","Triangle","SawTooth"});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startPlot_clicked()
{

}


void MainWindow::on_stopPlot_clicked()
{

}


void MainWindow::on_resetPlot_clicked()
{

}

