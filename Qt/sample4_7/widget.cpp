#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnGetTime_clicked()
{
    // 读取当前日期时间按钮
    QDateTime curDateTime=QDateTime::currentDateTime();//读取当前日期时间
    ui->timeEdit->setTime(curDateTime.time());//设置时间
    ui->editTime->setText(curDateTime.toString("hh:mm:ss"));
    ui->dateEdit->setDate(curDateTime.date());//设置日期
    ui->editDate->setText(curDateTime.toString("yyyy-MM-dd"));
    ui->dateTimeEdit->setDateTime(curDateTime);//设置日期时间
    ui->editDateTime->setText(curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}


void Widget::on_btnSetTime_clicked()
{
    QString str=ui->editTime->text();
    str=str.trimmed();
    if(!str.isEmpty())
    {
        QTime tm=QTime::fromString(str,"hh:mm:ss");
        ui->timeEdit->setTime(tm);
    }
}


void Widget::on_btnSetDate_clicked()
{
    QString str=ui->editDate->text();
    str=str.trimmed();
    if(!str.isEmpty())
    {
        QDate dt=QDate::fromString(str,"yyyy-MM-dd");
        ui->dateEdit->setDate(dt);
    }
}


void Widget::on_btnSetDateTime_clicked()
{
    QString str=ui->editDateTime->text();
    str=str.trimmed();
    if(!str.isEmpty())
    {
        QDateTime dateTime=QDateTime::fromString(str,"yyyy-MM-dd hh:mm:ss");
        ui->dateTimeEdit->setDateTime(dateTime);
    }
}


void Widget::on_calendarWidget_selectionChanged()
{
    QDate dt=ui->calendarWidget->selectedDate();
    QString str=dt.toString("yyyy年M月d日");
    ui->editCalendar->setText(str);
}

