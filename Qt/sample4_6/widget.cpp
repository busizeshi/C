#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 将表盘、滑动条、卷滚条的valueChanged()信号与自定义槽函数关联
    connect(ui->slider,SIGNAL(valueChanged(int)),this,SLOT(do_valueChanged(int)));
    connect(ui->scrollBar,SIGNAL(valueChanged(int)),this,SLOT(do_valueChanged(int)));
    connect(ui->dial,SIGNAL(valueChanged(int)),this,SLOT(do_valueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_valueChanged(int value)
{
    // 设置进度条的value
    ui->progressBar->setValue(value);
}

void Widget::on_chkBox_Visible_clicked(bool checked)
{
    ui->progressBar->setTextVisible(checked);
}


void Widget::on_chkBox_Inverted_clicked(bool checked)
{
    ui->progressBar->setInvertedAppearance(checked);
}


void Widget::on_radio_Percent_clicked()
{
    // 显示百分比
    ui->progressBar->setFormat("%p%");
}


void Widget::on_radio_Value_clicked()
{
    // 显示当前值
    ui->progressBar->setFormat("%v%");
}

