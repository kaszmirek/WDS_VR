#ifndef COMUNICATION_H
#define COMUNICATION_H

#include <QMainWindow>
#include <QtDebug>
#include <QSerialPortInfo>
#include <QList>
#include <QDateTime>
#include <QSerialPort>
#include <QMetaObject>
#include <QFloat16>
#include <iostream>
#include <QVector3D>
#include <string>

class communication{
public:

    communication(QWidget *parent);



    /**
     * @brief Make UART connection
     * @param portName
     * @retval true connected
     * @retval false not connected
     */
    bool setUARTConnection(QString portName);

    /**
     * @brief Disconnect UART connection
     */
    void disconnectUARTConnection(){this->device->close();};

    /**
     * @retval true is open
     * @retval false is closed
     */
    bool isDeviceOpen();

    /**
     * @brief Read data from UART and change accelerometerData_x/y/z value
     */
    void readData();

    QVector3D getAccelerometerData();

private:
    QSerialPort *device;
    QWidget *parent;
    QVector3D accelerometerData;
};

#endif // COMUNICATION_H
