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
     * @brief Read data from UART and change imuData_q1/q2/q3 value
     */
    void readData();

    QVector3D getImuData();

private:
    QSerialPort *device;
    QWidget *parent;
    QVector3D imuData;
};

#endif // COMUNICATION_H
