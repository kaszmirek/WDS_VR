#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QSerialPortInfo>
#include <QList>
#include <QDateTime>
#include <QSerialPort>
#include <comunication.h>
#include <QTimer>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlProperty>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void fromDeviceToProgram_timer();

private slots:

    void on_pushButton_search_clicked();
    void on_pushButton_connect_clicked();

    /**
     * @brief Show or hide configuration panel
     */
    void on_actionDevice_configuration_triggered();

    void on_actionExit_triggered();


    /**
     * @brief Disconnect UART connection
     */
    void on_pushButton_disconnect_clicked();

private:
    Ui::MainWindow *ui;
    communication device;
    QTimer *timer;

    void addToLogs(QString message);

};
#endif // MAINWINDOW_H
