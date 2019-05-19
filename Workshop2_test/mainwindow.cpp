#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QSerialPortInfo>
#include <QFile>
#include <qfile.h>
#include <QTextStream>
#include <QStringList>
#include <QIODevice>
#include <iostream>
#include <QtCore>
#include <QDateTime>
#include <QSerialPortInfo>
#include <QIODevice>







QTextStream out(stdout);



QSerialPort * serial;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);

    //serialBuffer = "";
    serial->setPortName("/dev/ttyACM0");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
    if (!serial->open(QIODevice::ReadWrite))
           {
            qDebug("some error when opening\n");

           }
    if(!serial->isOpen()){

         ui->conLabel->setText("<font color='red'>Not connected</font>");
    }

    serial->write("ok");
    connect(serial, SIGNAL(readyRead()), this, SLOT(serialReceived()));

}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();

}

void MainWindow::serialReceived() {
  QString validLine;
  while (serial->canReadLine()) {
    auto binLine = serial->readLine();
    auto line = QString::fromLatin1(binLine);
    if (line.length() < 8){
        continue;
    }
    validLine = line;

  if (validLine.isEmpty()) return;
  auto hum = line.left(2);
  auto temp = line.mid(5, 2);
  ui->humLabel->setText(QStringLiteral("Humidity: %1%").arg(hum));
  ui->tempLabel->setText(QStringLiteral("Temperature: %1°C").arg(temp));

  QFile data("/home/jvelgaard/projects/SSU-Workshop2/Workshop2_test/csv.csv");


  if (data.open(QFile::WriteOnly | QFile::Append)) {
      QTextStream out(&data);



      out <<  QDate::currentDate().toString()<< "," << QTime::currentTime().toString() << "," << hum << "," << temp << '\n';


  }

  }
}




void MainWindow::on_pushButton_clicked()
{
    this->hide();

}
