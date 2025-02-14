#include "widget.h"
#include "ui_widget.h"

#include <QTimer>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->groupBox->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    ui->groupBox_3->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    m_timer=new QTimer(this);
    m_timer->stop();
    m_timer->setTimerType(Qt::CoarseTimer);
    ui->radioCoarse->setChecked(true);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(do_timer_timeout()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_timer_timeout()
{
    QApplication::beep();                              //使系统“嘀”一声
    QTime curTime= QTime::currentTime();               //获取当前时间
    ui->LCDHour->display(curTime.hour());              //LCD 显示  小时
    ui->LCDMin->display(curTime.minute());             //LCD 显示  分钟
    ui->LCDSec->display(curTime.second());             //LCD 显示  秒
    if (m_timer->isSingleShot())                       //如果是单次定时，显示流逝的时间
    {
        int tmMsec= m_counter.elapsed();               //毫秒数
        QString str= QString("流逝的时间：%1 毫秒").arg(tmMsec);
        ui->label->setText(str);
        ui->btnStart->setEnabled(true);
        ui->btnOneShot->setEnabled(true);
        ui->btnStop->setEnabled(false);
    }
}

void Widget::do_timer_shot()
{
    QApplication::beep();
    int tmMsec= m_counter.elapsed();                   //流逝的时间，单位：毫秒
    QString str= QString("流逝的时间：%1 毫秒").arg(tmMsec);
    ui->label->setText(str);
    ui->btnOneShot->setEnabled(true);
}

void Widget::on_btnStart_clicked()
{
    m_timer->setInterval(ui->spinBoxIntv->value());//设置定时器的周期
    if(ui->radioContiue->isChecked())
        m_timer->setSingleShot(false);//设置为连续定时
    else
        m_timer->setSingleShot(true);//设置为单次定时

    if(ui->radioPrecise->isChecked())
        m_timer->setTimerType(Qt::PreciseTimer);
    else if(ui->radioCoarse->isChecked())
        m_timer->setTimerType(Qt::CoarseTimer);
    else
        m_timer->setTimerType(Qt::VeryCoarseTimer);

    m_timer->start();
    m_counter.start();
    ui->btnStart->setEnabled(false);
    ui->btnOneShot->setEnabled(false);
    ui->btnStop->setEnabled(true);
}


void Widget::on_btnStop_clicked()
{
    m_timer->stop();//定时器停止
    int tmMsec=m_counter.elapsed();
    int ms=tmMsec%1000;
    int sec=tmMsec/1000;
    QString str=QString("流逝的时间:%1秒,%2毫秒").arg(sec).arg(ms,3,10,QChar('0'));
    ui->label->setText(str);
    ui->btnStart->setEnabled(true);
    ui->btnOneShot->setEnabled(true);
    ui->btnStop->setEnabled(false);
}


void Widget::on_btnOneShot_clicked()
{
    int intv= ui->spinBoxIntv->value();                //定时周期
    QTimer::singleShot(intv, Qt::PreciseTimer, this, &Widget::do_timer_shot);
    m_counter.start();                                 //启动计时器
    ui->btnOneShot->setEnabled(false);
}

