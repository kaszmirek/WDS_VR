#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , device(parent)
{
    ui->setupUi(this);
    ui->stackedWidget_main->setCurrentWidget(ui->stackedWidget_program);

    QPalette pal = ui->stackedWidget_program->palette();
    pal.setColor(QPalette::Background, Qt::black);

    ui->stackedWidget_program->setAutoFillBackground(true);
    ui->stackedWidget_program->setPalette(pal);

    ui->centralwidget->setAutoFillBackground(true);
    ui->centralwidget->setPalette(pal);
    ui->groupBox_logs->setStyleSheet("QGroupBox  {color: white;}");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(fromDeviceToProgram_timer()));
    timer->start(10);

    ui->quickWidget->setSource(QUrl(QStringLiteral( "qrc:/main.qml")));
    ui->quickWidget->engine()->rootContext()->setContextProperty("_accX", 0);
    ui->quickWidget->engine()->rootContext()->setContextProperty("_accY", 0);
    ui->quickWidget->engine()->rootContext()->setContextProperty("_accZ", 0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_search_clicked()
{
    this->addToLogs( "Searching...");
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    ui->comboBox_devices->clear();
    if ( !devices.count()){
        this->addToLogs("No device detected");
        return;
    }
    for(int i = 0; i < devices.count(); i++) {
      this->addToLogs( "Device detected: " + devices.at(i).portName() + " " + devices.at(i).description());
      ui->comboBox_devices->addItem(devices.at(i).portName() + "\t" + devices.at(i).description());
    }
}

void MainWindow::addToLogs(QString message){
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEdit_logs->append(currentDateTime + "\t" + message);
}

void MainWindow::on_pushButton_connect_clicked()
{
    if(ui->comboBox_devices->count() == 0) {
      this->addToLogs("No device detected!");
      return;
    }

    if(this->device.isDeviceOpen()){
      this->addToLogs("This port has been already opened!");
        return;
    }

    QString portName =  ui->comboBox_devices->currentText().split("\t").first();
    this->addToLogs("Trying to open " + portName);
    if(this->device.setUARTConnection(portName)){
      this->addToLogs("Serial port opened");
    }
    else this->addToLogs("Error: serial port can't be opened");
}



void MainWindow::on_actionDevice_configuration_triggered()
{
   if( ui->stackedWidget_main->currentWidget() == ui->stackedWidget_program){
        ui->textEdit_logs->clear();
        ui->stackedWidget_main->setCurrentWidget(ui->stackedWidget_options);

   }
   else{
       ui->stackedWidget_main->setCurrentWidget(ui->stackedWidget_program);
   }
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}


void MainWindow::on_pushButton_disconnect_clicked()
{
    this->device.disconnectUARTConnection();
    this->addToLogs("Serial port closed");
}

void MainWindow::fromDeviceToProgram_timer(){
    if(device.isDeviceOpen()){
        device.readData();
        QVector3D data = device.getAccelerometerData();
        ui->quickWidget->engine()->rootContext()->setContextProperty("_accX", data.x());
        ui->quickWidget->engine()->rootContext()->setContextProperty("_accY", data.y());
        ui->quickWidget->engine()->rootContext()->setContextProperty("_accZ", data.z());
        qDebug() <<  data;
  }
}
