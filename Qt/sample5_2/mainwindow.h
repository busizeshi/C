#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QStandardItemModel;
class QItemSelectionModel;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

#define FixedColumnCount 6 //文件固定为6列

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel *labCurFile;//当前文件
    QLabel *labCellPos;//当前单元格行列号
    QLabel *labCellText;//当前单元格内容
    QStandardItemModel *m_model;//数据模型
    QItemSelectionModel *m_selection;//选择模型
    void iniModelData(QStringList &aFileContent);//从StringList初始化数据模型内容

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
// 自定义槽函数，与QItemSelectionModel的currentChanged()信号连接
    void do_currentChanged(const QModelIndex &current,const QModelIndex &previous);

private slots:
    void on_actOpen_triggered();

    void on_actAppend_triggered();

    void on_actDelete_triggered();

    void on_actAlignLeft_triggered();

    void on_actFontBold_triggered();

    void on_actFontBold_toggled(bool arg1);

    void on_actFontBold_triggered(bool checked);

    void on_actModelData_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
