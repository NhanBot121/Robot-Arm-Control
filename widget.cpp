#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QString>
#include <QSerialPort>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Title
    QWidget::setWindowTitle("Robot Arm Control");

    // Ports
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0; i < ports.size(); i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->portBox->addItems(stringPorts);

    // Baud Rate
    QList<qint32> baudRates = info.standardBaudRates();
    QList<QString> stringBaudRates;
    for(int i = 0; i < baudRates.size(); i++) {
        stringBaudRates.append(QString::number(baudRates.at(i)));
    }
    ui->baudrateBox->addItems(stringBaudRates);

    connect(ui->connectButton, &QPushButton::clicked,
            this, &Widget::Connect);
    connect(ui->disconnectbutton, &QPushButton::clicked,
            this, &Widget::Disconnect);

    connect(ui->s1, SIGNAL(valueChanged(int)),
            this, SLOT(Servo1(int)));
    connect(ui->s2, SIGNAL(valueChanged(int)),
            this, SLOT(Servo2(int)));
    connect(ui->s3, SIGNAL(valueChanged(int)),
            this, SLOT(Servo3(int)));

    connect(ui->saveButton, &QPushButton::clicked,
            this, &Widget::Save);
    connect(ui->runButton, &QPushButton::clicked,
            this, &Widget::Run);
    connect(ui->resetButton, &QPushButton::clicked,
            this, &Widget::Reset);

}

Widget::~Widget()
{
    delete ui;
}

// Connect
void Widget::Connect()
{
    // Set Port
    QString portName = ui->portBox->currentText();
    serialPort.setPortName(portName);

    serialPort.open(QIODevice::ReadWrite);

    if(!serialPort.isOpen()) {
        ui->connectStatus->setText("Connect Failed");
        qDebug() << serialPort.isOpen();
    }
    else {
        // Set Baud Rate
        ui->connectStatus->setText("Connected");
        QString stringBaudRate = ui->baudrateBox->currentText();
        int intbaudrate = stringBaudRate.toInt();
        serialPort.setBaudRate(intbaudrate);
        qDebug() << serialPort.isOpen();
    }
}

// Disconnect
void Widget::Disconnect()
{
    serialPort.close();
    ui->connectStatus->setText("Disconnected");
    qDebug() << serialPort.isOpen();
}

// Control Servos
void Widget::Servo1(int angle)
{
    ui->waist->setText(QString("Waist: %1 degree")
                       .arg(angle));
    QString angleStr = QString("s1") + QString::number(angle);
    const char* val = angleStr.toStdString().c_str();
    qDebug() << val;
    serialPort.write(val);
}
void Widget::Servo2(int angle)
{
    ui->shoulder->setText(QString("Shoulder: %1 degree")
                       .arg(angle));
    QString angleStr = QString("s2") + QString::number(angle);
    const char* val = angleStr.toStdString().c_str();
    qDebug() << val;
    serialPort.write(val);
}
void Widget::Servo3(int angle)
{
    ui->elbow->setText(QString("Elbow: %1 degree")
                       .arg(angle));
    QString angleStr = QString("s3") + QString::number(angle);
    const char* val = angleStr.toStdString().c_str();
    qDebug() << val;
    serialPort.write(val);
}

// Save
void Widget::Save()
{
    serialPort.write("SAVE");
    qDebug() << "Save";
    qDebug() << serialPort.readAll();

}

// Run
void Widget::Run()
{
    serialPort.write("RUN");
    qDebug() << "Run";
}

// Reset
void Widget::Reset()
{
    serialPort.write("RESET");
    qDebug() << "Reset";
}

