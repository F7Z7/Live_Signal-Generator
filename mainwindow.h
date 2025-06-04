#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMainWindow>
#include <QTimer>
#include <QVector>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startPlot_clicked();

    void on_stopPlot_clicked();
    // void generatePlot(const QString &type, double freq);
    void update_plot();
    void on_resetPlot_clicked();

private:
    //declaring necessary variables
    Ui::MainWindow *ui;
    QTimer *timer;
    double freq,t,dt;
    QVector<double> X,Y;
};
#endif // MAINWINDOW_H
