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

void Widget::on_btnIniItems_clicked()
{//“初始化列表”按钮
    QIcon  icon;
    icon.addFile(":/images/icons/aim.ico");                    //从资源文件中获取图标
    ui->comboBox->clear();                                     //清除列表
    for (int i=0; i<20; i++)
        ui->comboBox->addItem(icon,QString("Item %1").arg(i)); //带有图标
    //      ui->comboBox->addItem(QString("Item %1").arg(i));      //不带有图标
}


void Widget::on_btnIni2_clicked()
{
    // QMap自动an找key排序
    QMap<QString,int> cityZone;
    cityZone.insert("北京",10);
    cityZone.insert("深证",21);
    cityZone.insert("上海",22);
    cityZone.insert("杭州",411);
    cityZone.insert("成都",416);
    cityZone.insert("苏州",516);
    ui->comboBox2->clear();
    foreach (const QString &str,cityZone.keys()) {
        ui->comboBox2->addItem(str,cityZone.value(str));
    }
}


void Widget::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}


void Widget::on_comboBox2_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    QString city=ui->comboBox2->currentText();
    QString zone=ui->comboBox2->currentData().toString();
    ui->plainTextEdit->appendPlainText(city+":区号="+zone);
}


void Widget::on_btnClearItems_clicked()
{
    ui->comboBox->clear();
}


void Widget::on_chkBoxEditable_clicked(bool checked)
{
    ui->comboBox->setEditable(checked);
}


void Widget::on_btnClearText_clicked()
{
    ui->plainTextEdit->clear();
}

