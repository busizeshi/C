#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnIniList_clicked();

    void on_btnListClear_clicked();

    void on_btnListAppend_clicked();

    void on_btnListInsert_clicked();

    void on_btnListDelete_clicked();

    void on_btnListMoveUp_clicked();

    void on_btnListMoveDown_clicked();

    void on_btnListSort_clicked(bool checked);

    void on_chkEditable_clicked(bool checked);

    void on_btnTextImport_clicked();

    void on_btnTextClear_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
