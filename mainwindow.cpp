#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QComboBox>
#include <QTimer>
#include <QMessageBox>
#include <QPen>
#include <cmath>


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
void MainWindow::on_startPlot_clicked()
{



   // generatePlot(signalType,freq);
    t=0;
   X.clear();
    Y.clear();
    timer->start(30);


}

void MainWindow::update_plot(){
    QString signalType = ui->signalDrop->currentText();
    freq = ui->freqInput->value();

    if (freq <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Frequency can't be negative or zero!");
        return;
    }

    dt = 0.05;
    t += dt;
    X.append(t);

    double value = 0;
    double phase = fmod(freq * t, 1.0);

    if (signalType == "Sine") {
        value = sin(2 * M_PI * freq * t);
    }
    else if (signalType == "Square") {
        value = (phase < 0.5) ? 1.0 : -1.0;
    }
    else if (signalType == "Triangle") {
        if (phase < 0.25)
            value = 4 * phase;
        else if (phase < 0.75)
            value = 2 - 4 * phase;
        else
            value = -4 + 4 * phase;
        value = 2 * value - 1; // Normalize to [-1,1]
    }
    else if (signalType == "SawTooth") {
        value = 2 * phase - 1;
    }
    else {
        value = 0;
    }

    Y.append(value);

    // Update graph data and legend
    ui->graphPlotter->graph(0)->setData(X, Y);
    ui->graphPlotter->graph(0)->setName(signalType);
    ui->graphPlotter->legend->setVisible(true);
    ui->graphPlotter->xAxis->setRange(t > 1 ? t - 1 : 0, t);
    ui->graphPlotter->yAxis->setRange(-1.5, 1.5);
    ui->graphPlotter->replot();
}

void MainWindow::on_stopPlot_clicked()
{
    timer->stop();
}


void MainWindow::on_resetPlot_clicked()
{

    timer->stop();
    t = 0;
    X.clear();
    Y.clear();
    ui->graphPlotter->clearGraphs();


    //readding the graph panel

    ui->graphPlotter->addGraph();
    ui->graphPlotter->graph(0)->setData(X,Y);
    ui->graphPlotter->graph(0)->setPen(QPen(Qt::blue));
    ui->graphPlotter->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->graphPlotter->xAxis->setRange(0, 1);
    ui->graphPlotter->yAxis->setRange(-1.5, 1.5);
     ui->graphPlotter->legend->setVisible(true);
    ui->graphPlotter->replot();


}

