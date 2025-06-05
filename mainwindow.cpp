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
    // If already plotting prevent double start
    if (startButtonClicked && !stopButtonClicked) {
        QMessageBox::warning(this, "Invalid Command", "The signal is already being plotted.");
        return;
    }

    // If plot exists but user hasn't stopped or reset, force reset first
    if (hasPlotted && !stopButtonClicked && !resetButtonClicked) {
        QMessageBox::critical(this, "Invalid Command", "Clear the existing graph before starting a new one.");
        return;
    }

    // If reset was clicked before or no plot exists, clear data and start fresh
    if (resetButtonClicked || !hasPlotted) {
        t = 0;
        X.clear();
        Y.clear();

        resetButtonClicked = false; // We are now starting fresh, so reset flag off
    }

    // If stopped before and plot exists, this is a resume
    if (stopButtonClicked && hasPlotted) {
        // QMessageBox::information(this, "Feedback", "Graph is resumed from the last position");
       //graph will resume
    }

    // Start or resume the timer once
    timer->start(50);

    // Update button states
    startButtonClicked = true;
    stopButtonClicked = false;
    hasPlotted = true;
}



void MainWindow::update_plot(){
    QString signalType = ui->signalDrop->currentText();
    freq = ui->freqInput->value();

    if (freq <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Frequency can't be negative or zero!");
        return;
    }

    //dt = 0.05;
    int samples=20;
    dt=1.0/(freq*samples);

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
        if (phase < 0.5)
            value = 4 * phase - 1;
        else
            value = 3 - 4 * phase;
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
    stopButtonClicked=true;
    hasPlotted=true;


}


void MainWindow::on_resetPlot_clicked()
{

    timer->stop();
    t = 0;
    X.clear();
    Y.clear();
    ui->graphPlotter->clearGraphs();
    resetButtonClicked=true;

    //readding the graph panel

    ui->graphPlotter->addGraph();
    ui->graphPlotter->graph(0)->setData(X,Y);
    ui->graphPlotter->graph(0)->setPen(QPen(Qt::blue));
    ui->graphPlotter->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->graphPlotter->xAxis->setRange(0, 1);
    ui->graphPlotter->yAxis->setRange(-1.5, 1.5);
     ui->graphPlotter->legend->setVisible(true);
    ui->graphPlotter->replot();

     resetButtonClicked = true;
     stopButtonClicked = false;
     startButtonClicked = false;
     hasPlotted = false;

}

