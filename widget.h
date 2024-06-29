#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    // Connection
    void Connect();
    void Disconnect();
    // Control
    void Servo1(int);
    void Servo2(int);
    void Servo3(int);
    // Action
    void Save();
    void Run();
    void Reset();

private:
    Ui::Widget *ui;
    QSerialPort serialPort;
    QSerialPortInfo info;

};

#endif // WIDGET_H
