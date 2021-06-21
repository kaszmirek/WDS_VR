#include "comunication.h"

communication::communication(QWidget *_parent){
    this->device = new QSerialPort(_parent);
    parent = _parent;
}

bool communication::setUARTConnection(QString portName){
    this->device->setPortName(portName);
    this->device->setBaudRate(QSerialPort::Baud115200);
    this->device->setDataBits(QSerialPort::Data8);
    this->device->setParity(QSerialPort::NoParity);
    this->device->setStopBits(QSerialPort::OneStop);
    this->device->setFlowControl(QSerialPort::NoFlowControl);

    if(this->device->open(QIODevice::ReadWrite)) {
       // QObject::connect(this->device, SIGNAL(readyRead()), this->parent, SLOT(readFromPort()));
      return true;
    }
    return false;
}


bool communication::isDeviceOpen(){
    return this->device->isOpen();
}


void communication::readData(){
    while(this->device->canReadLine()) {
    QString line = this->device->readLine();
    QString terminator = "\r";
    int pos = line.lastIndexOf(terminator);
    imuData.setX((line.left(pos).split("\t")[0].toFloat()));
    imuData.setY((line.left(pos).split("\t")[1].toFloat()));
    imuData.setZ((line.left(pos).split("\t")[2].toFloat()));
    }
}

QVector3D communication::getImuData(){return this->imuData;}
