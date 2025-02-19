#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QStringListModel>

QStringList m_strList;//保存初始字符串列表内容
QStringListModel *m_model;//数据模型

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化一个字符串列表的内容
    m_strList<<"阿拉斯加"<<"哈士奇"<<"萨摩耶"<<"金毛"<<"边牧"<<"柯基";
    m_model=new QStringListModel(this);//创建数据模型
    m_model->setStringList(m_strList);//初始化数据
    ui->listView->setModel(m_model);
    ui->chkEditable->setChecked(true);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnIniList_clicked()
{
    m_model->setStringList(m_strList);
}


void MainWindow::on_btnListClear_clicked()
{
    m_model->removeRows(0,m_model->rowCount());
}


void MainWindow::on_btnListAppend_clicked()
{
    m_model->insertRow(m_model->rowCount());
    QModelIndex index=m_model->index(m_model->rowCount()-1,0);
    m_model->setData(index,"new item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_btnListInsert_clicked()
{
    QModelIndex index=ui->listView->currentIndex();
    m_model->insertRow(index.row());
    m_model->setData(index,"inserted item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_btnListDelete_clicked()
{
    QModelIndex index=ui->listView->currentIndex();
    m_model->removeRow(index.row());
}


void MainWindow::on_btnListMoveUp_clicked()
{
    int curRow=ui->listView->currentIndex().row();
    QModelIndex index=QModelIndex();
    m_model->moveRow(index,curRow,index,curRow-1);
}


void MainWindow::on_btnListMoveDown_clicked()
{
    int curRow=ui->listView->currentIndex().row();
    QModelIndex index=QModelIndex();
    m_model->moveRow(index,curRow,index,curRow+2);
}


void MainWindow::on_btnListSort_clicked(bool checked)
{
    if(checked)
        m_model->sort(0,Qt::AscendingOrder);
    else
        m_model->sort(0,Qt::DescendingOrder);
}


void MainWindow::on_chkEditable_clicked(bool checked)
{
    if(checked)
        ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
    else
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::on_btnTextImport_clicked()
{
    QStringList tmpList=m_model->stringList();
    ui->plainTextEdit->clear();
    for(int i=0;i<tmpList.size();i++)
        ui->plainTextEdit->appendPlainText(tmpList.at(i));
}


void MainWindow::on_btnTextClear_clicked()
{
    ui->plainTextEdit->clear();
}

