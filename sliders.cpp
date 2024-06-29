#include "sliders.h"
#include "ui_sliders.h"

sliders::sliders(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sliders)
{
    ui->setupUi(this);
}

sliders::~sliders()
{
    delete ui;
}

void sliders::Servo1(int angle)
{
    serialPort.write("s140");
}


