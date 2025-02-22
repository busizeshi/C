#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QFileDialog>

void MainWindow::iniModelData(QStringList &aFileContent)
{
    int rowCnt=aFileContent.size();
    m_model->setRowCount(rowCnt-1);
    QString header=aFileContent.at(0);
    QStringList headerList=header.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
    m_model->setHorizontalHeaderLabels(headerList);//设置表头文字

    // 设置表格数据
    int j;
    QStandardItem *aItem;
    for(int i=1;i<rowCnt;i++)
    {
        QString aLineText=aFileContent.at(i);
        QStringList tmpList=aLineText.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
        for(j=0;j<FixedColumnCount-1;j++)
        {
            aItem=new QStandardItem(tmpList.at(j));
            m_model->setItem(i-1,j,aItem);
        }
        aItem=new QStandardItem(headerList.at(j));
        aItem->setCheckable(true);
        aItem->setBackground(QBrush(Qt::yellow));
        if(tmpList.at(j)=="0")
            aItem->setCheckState(Qt::Unchecked);
        else
            aItem->setCheckState(Qt::Checked);
        m_model->setItem(i-1,j,aItem);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model=new QStandardItemModel(2,FixedColumnCount,this);
    m_selection=new QItemSelectionModel(m_model,this);
    // 选择当前单元格变化时的信号与槽
    connect(m_selection,&QItemSelectionModel::currentChanged,this,&MainWindow::do_currentChanged);
    // 为tableView设置数据模型和选择模型
    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionModel(m_selection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    setCentralWidget(ui->splitter);
    // 创建状态栏组件
    labCurFile=new QLabel("当前文件: ",this);
    labCurFile->setMinimumWidth(200);
    labCellPos=new QLabel("当前单元格: ",this);
    labCellPos->setMinimumWidth(180);
    labCellPos->setAlignment(Qt::AlignHCenter);
    labCellText=new QLabel("单元格内容: ",this);
    labCellText->setMinimumWidth(150);
    ui->statusbar->addWidget(labCurFile);
    ui->statusbar->addWidget(labCellPos);
    ui->statusbar->addWidget(labCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if(current.isValid())
    {
        labCellPos->setText(QString::asprintf("当前单元格: %d行,%d列",current.row(),current.column()));
        QStandardItem *aItem=m_model->itemFromIndex(current);
        labCellText->setText("单元格内容："+aItem->text());
        QFont font=aItem->font();
        ui->actFontBold->setChecked(font.bold());
    }
}

void MainWindow::on_actOpen_triggered()
{
    QString curPath=QCoreApplication::applicationDirPath();//获取应用程序的路径
    QString aFileName=QFileDialog::getOpenFileName(this,"打开一个文件",curPath,"数据文件(*.txt);;所有文件(*.*)");
    if(aFileName.isEmpty())
        return;
    QStringList aFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream aStream(&aFile);
        ui->plainTextEdit->clear();
        while(!aStream.atEnd())
        {
            QString str=aStream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            aFileContent.append(str);
        }
        aFile.close();
        labCurFile->setText("当前文件: "+aFileName);
        ui->actAppend->setEnabled(true);
        ui->actInsert->setEnabled(true);
        ui->actDelete->setEnabled(true);
        ui->actSave->setEnabled(true);
        iniModelData(aFileContent);
    }
}


void MainWindow::on_actAppend_triggered()
{
    //“添加行”按钮
    QList<QStandardItem*>    aItemList;
    QStandardItem   *aItem;
    for(int i=0; i<FixedColumnCount-1; i++)                          //不包含最后一列
    {
        aItem= new QStandardItem("0");
        aItemList<<aItem;     //添加到列表
    }
    //获取最后一列的表头文字
    QString str= m_model->headerData(m_model->columnCount()-1, Qt::Horizontal,
                                      Qt::DisplayRole).toString();
    aItem= new QStandardItem(str);
    aItem->setCheckable(true);
    aItemList<<aItem;                                                 //添加到列表
    m_model->insertRow(m_model->rowCount(),aItemList);                //插入一行
    QModelIndex curIndex=m_model->index(m_model->rowCount()-1,0);     //获取模型索引
    m_selection->clearSelection();
    m_selection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
}


void MainWindow::on_actDelete_triggered()
{
    //“删除行”按钮
    QModelIndex curIndex= m_selection->currentIndex(); //获取当前单元格的模型索引
    if (curIndex.row() == m_model->rowCount()-1)       //最后一行
        m_model->removeRow(curIndex.row());            //删除最后一行
    else
    {
        m_model->removeRow(curIndex.row());            //删除一行，并重新设置当前选择项
        m_selection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
}


void MainWindow::on_actAlignLeft_triggered()
{

}


void MainWindow::on_actFontBold_triggered(bool checked)
{
    //设置字体为粗体
    if (!m_selection->hasSelection())
        return;
    //获取选择单元格的模型索引列表
    QModelIndexList selectedIndex= m_selection->selectedIndexes();
    for (int i=0; i<selectedIndex.count(); i++)
    {
        QModelIndex aIndex= selectedIndex.at(i);                   //获取一个模型索引
        QStandardItem* aItem= m_model->itemFromIndex(aIndex);      //获取项
        QFont font= aItem->font();
        font.setBold(checked);
        aItem->setFont(font);
    }
}


void MainWindow::on_actModelData_triggered()
{
    //模型数据导出到plainTextEdit中显示
    ui->plainTextEdit->clear();
    QStandardItem   *aItem;
    QString str;
    //获取表头文字
    for (int i=0; i<m_model->columnCount(); i++)
    {
        aItem= m_model->horizontalHeaderItem(i);                 //获取表头的一个项
        str=str+aItem->text()+"\t";                              //用制表符分隔文字
    }
    ui->plainTextEdit->appendPlainText(str);
    //获取数据区的每行
    for (int i=0; i<m_model->rowCount(); i++)
    {
        str="";
        for(int j=0; j<m_model->columnCount()-1; j++)
        {
            aItem= m_model->item(i,j);
            str= str+aItem->text()+QString::asprintf("\t");      //以制表符分隔
        }
        aItem= m_model->item(i, FixedColumnCount-1);             //最后一行是逻辑型数据
        if (aItem->checkState() == Qt::Checked)
            str= str+"1";
        else
            str= str+"0";
        ui->plainTextEdit->appendPlainText(str);
    }
}

