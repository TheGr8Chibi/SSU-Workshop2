#include "mainwindow.h"
#include <QApplication>
#include <QtSerialPort/QSerialPort>
#include <QLabel>
#include <QDebug>
using namespace std;



int main(int argc, char *argv[])
{
    string temp;
    string humi;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QSerialPort port;
    port.setPortName("COM3");
    port.setBaudRate(250000);
    port.setDataBits(QSerialPort::Data8);
    port.setParity(QSerialPort::NoParity);
    port.setStopBits(QSerialPort::OneStop);
    port.setFlowControl(QSerialPort::NoFlowControl);
    port.open(QIODevice::ReadWrite);


    for(int i=1;i<10;i++){

    if(!port.waitForReadyRead(-1)){ //block until new data arrives
        qDebug() << "error: " << port.errorString();
    }
    else{
        QByteArray datas;
        datas = port.readAll();

        if (datas.at(0) == '#'){
            temp.assign(datas);
            QString temp = datas;
            qDebug() << temp;
        }
        else if (datas.at(0) == '&'){
            humi.assign(datas);
            QString humi = datas;
            qDebug() << humi;
        }


    }
    }

    return a.exec();
}
