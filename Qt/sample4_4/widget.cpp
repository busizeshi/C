#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->spinNum,SIGNAL(valueChanged(int)), this,SLOT(on_btnCal_clicked()));
    connect(ui->spinPrice,SIGNAL(valueChanged(double)), this,SLOT(on_btnCal_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnCal_clicked()
{
    int num=ui->spinNum->value();
    float price=ui->spinPrice->value();
    float total=num*price;
    ui->spinTotal->setValue(total);
}

void Widget::on_spinBox_2_valueChanged(int arg1)
{
    qDebug(ui->spinDec->cleanText().toLocal8Bit().data());
    ui->spinBox_3->setValue(arg1);
    ui->spinBox_4->setValue(arg1);
}


void Widget::on_spinBox_3_valueChanged(int arg1)
{
    qDebug(ui->spinBox_3->cleanText().toLocal8Bit().data());  //显示数值的二进制字符串
    ui->spinDec->setValue(arg1);
    ui->spinBox_4->setValue(arg1);
}


void Widget::on_spinBox_4_valueChanged(int arg1)
{
    qDebug(ui->spinBox_4->cleanText().toLocal8Bit().data());  //显示数值的十六进制字符串
    ui->spinDec->setValue(arg1);
    ui->spinBox_3->setValue(arg1);
}

