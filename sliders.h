#ifndef SLIDERS_H
#define SLIDERS_H

#include <QWidget>

namespace Ui {
class sliders;
}

class sliders : public QWidget
{
    Q_OBJECT

public:
    explicit sliders(QWidget *parent = nullptr);
    ~sliders();

public slots:
    void Servo1(int);
    void Servo2(int);
    void Servo3(int);
    void Servo4(int);
    void Servo5(int);
    void Servo6(int);

private:
    Ui::sliders *ui;
};

#endif // SLIDERS_H
