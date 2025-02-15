#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    setActionsForButton();
    createSelectionMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActionsForButton()
{
    // 为各个QToolButton类按钮设置action
    ui->tBtnListIni->setDefaultAction(ui->actListIni);//初始化列表
    ui->tBtnListClear->setDefaultAction(ui->actListClear);//清除列表
    ui->tBtnListInsert->setDefaultAction(ui->actListInsert);//插入项
    ui->tBtnListAppend->setDefaultAction(ui->actListAppend);//添加项
    ui->tBtnListDelete->setDefaultAction(ui->actListDelete);//删除当前项
    ui->tBtnSelALL->setDefaultAction(ui->actSelALL);//全选
    ui->tBtnSelNone->setDefaultAction(ui->actSelNone);//空选
    ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);//反选
}

void MainWindow::createSelectionMenu()
{
    QMenu* menuSelection=new QMenu(this);
    menuSelection->addAction(ui->actSelALL);
    menuSelection->addAction(ui->actSelNone);
    menuSelection->addAction(ui->actSelInvs);

    ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);//菜单弹出模式
    ui->tBtnSelectItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tBtnSelectItem->setDefaultAction(ui->actSelPopMenu);//关联Action
    ui->tBtnSelectItem->setMenu(menuSelection);//设置下拉菜单

    QToolButton *aBtn=new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    aBtn->setDefaultAction(ui->actSelPopMenu);
    aBtn->setMenu(menuSelection);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actQuit);
}

void MainWindow::on_actListIni_triggered()
{
    // 初始化列表Action
    QListWidgetItem *aItem;
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk=ui->chkBoxListEditable->isChecked();

    ui->listWidget->clear();
    for(int i=0;i<10;i++)
    {
        QString str=QString("Item %1").arg(i);
        aItem=new QListWidgetItem();
        aItem->setText(str);
        aItem->setIcon(aIcon);
        aItem->setCheckState(Qt::Checked);
        if(chk)
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable
                            |Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        else
            aItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);

        ui->listWidget->addItem(aItem);
    }
}


void MainWindow::on_actListClear_triggered()
{
    ui->listWidget->clear();
}


void MainWindow::on_actListInsert_triggered()
{
    QIcon aIcon(":/images/icons/check2.ico");                 //定义图标变量并直接赋值
    bool chk= ui->chkBoxListEditable->isChecked();            //是否可编辑
    QListWidgetItem* aItem= new QListWidgetItem("Inserted Item");
    aItem->setIcon(aIcon);                                    //设置图标
    aItem->setCheckState(Qt::Checked);                        //设置为 checked
    if (chk)    //可编辑，设置 flags
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable
                        |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable
                        |Qt::ItemIsEnabled);
    ui->listWidget->insertItem(ui->listWidget->currentRow(),aItem);     //插入一个项
}


void MainWindow::on_actListAppend_triggered()
{
    QIcon aIcon(":/images/icons/check2.ico");                 //定义图标
    bool chk= ui->chkBoxListEditable->isChecked();            //是否可编辑
    QListWidgetItem* aItem= new QListWidgetItem("Added Item");
    aItem->setIcon(aIcon);                                    //设置图标
    aItem->setCheckState(Qt::Checked);                        //设置为 checked
    if (chk)                                                  //可编辑，设置 flags
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable
                        |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable
                        |Qt::ItemIsEnabled);
    ui->listWidget->addItem(aItem);                           //添加一个项
}


void MainWindow::on_actListDelete_triggered()
{
    int row= ui->listWidget->currentRow();                    //当前行的行号
    QListWidgetItem* aItem= ui->listWidget->takeItem(row);    //移除指定行的项
    delete aItem;    //需要手动删除对象
}


void MainWindow::on_actSelInvs_triggered()
{
    QListWidgetItem *aItem;
    int cnt= ui->listWidget->count();                         //项的个数
    for (int i=0; i<cnt; i++)
    {
        aItem= ui->listWidget->item(i);                       //获取一个项
        if (aItem->checkState()!=Qt::Checked)
            aItem->setCheckState(Qt::Checked);
        else
            aItem->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_tBtnSortAsc_clicked()
{
    ui->listWidget->sortItems(Qt::AscendingOrder);
}


void MainWindow::on_tBtnSortDes_clicked()
{
    ui->listWidget->sortItems(Qt::DescendingOrder);
}


void MainWindow::on_chkBoxSorting_clicked(bool checked)
{
    ui->listWidget->setSortingEnabled(checked);
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if (current != nullptr)                                 //需要检测指针是否为空
    {
        if (previous == nullptr)                            //需要检测指针是否为空
            str= "当前："+current->text();
        else
            str= "前一项："+previous->text()+"; 当前项："+current->text();
        ui->editCutItemText->setText(str);
    }
    ui->plainTextEdit->appendPlainText("currentItemChanged()信号被发射");
}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->plainTextEdit->appendPlainText(
        QString("currentRowChanged()信号被发射，currentRow=%1").arg(currentRow));
}


void MainWindow::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->plainTextEdit->appendPlainText(
        "currentTextChanged()信号被发射，currentText="+currentText);
}


void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemChanged()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemSelectionChanged()
{
    ui->plainTextEdit->appendPlainText("itemSelectionChanged()信号被发射");
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu* menuList= new QMenu(this);                     //创建菜单
    //添加 Action 将其作为菜单项
    menuList->addAction(ui->actListIni);
    menuList->addAction(ui->actListClear);
    menuList->addAction(ui->actListInsert);
    menuList->addAction(ui->actListAppend);
    menuList->addAction(ui->actListDelete);
    menuList->addSeparator();
    menuList->addAction(ui->actSelALL);
    menuList->addAction(ui->actSelNone);
    menuList->addAction(ui->actSelInvs);
    menuList->exec(QCursor::pos());                      //在鼠标光标位置显示快捷菜单
    delete menuList;                                     //菜单显示完后，需要删除对象
}

