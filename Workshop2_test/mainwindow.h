#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void serialReceived();


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString serialBuffer;
    QByteArray ba;
};



#endif // MAINWINDOW_H
