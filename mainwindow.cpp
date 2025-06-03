#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qcustomplot.h"
#include <QComboBox>
#include <QTimer>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->signalDrop->addItems({"Sine","Square","Triangle","SawTooth"});
    timer= new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update_plot);
    ui->graphPlotter->addGraph();
    ui->graphPlotter->graph(0)->setData(X,Y);
    ui->graphPlotter->graph(0)->setPen(QPen(Qt::blue));
    ui->graphPlotter->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->graphPlotter->xAxis->setRange(0, 1);
    ui->graphPlotter->yAxis->setRange(-1.5, 1.5);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::generatePlot(const QString &type, double freq){
    int sampleRate = 1000;
    int N = 1000;
    double dt = 1.0/sampleRate; //sampled evry second

}
void MainWindow::on_startPlot_clicked()
{

    QString signalType =ui->signalDrop->currentText();
   freq=ui->freqInput->value();

    if(freq<=0){
        QMessageBox::warning(this, "Invalid Input", "Frequency can't be negative or zero!");

    }
   generatePlot(signalType,freq);
    timer->start(30);

}

void MainWindow::update_plot(){

}
void MainWindow::on_stopPlot_clicked()
{

}


void MainWindow::on_resetPlot_clicked()
{

}

