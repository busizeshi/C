#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListWidgetItem;

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
    void setActionsForButton();
    void createSelectionMenu();


private slots:
    void on_actListIni_triggered();

    void on_actListClear_triggered();

    void on_actListInsert_triggered();

    void on_actListAppend_triggered();

    void on_actListDelete_triggered();

    void on_actSelInvs_triggered();

    void on_tBtnSortAsc_clicked();

    void on_tBtnSortDes_clicked();

    void on_chkBoxSorting_clicked(bool checked);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_listWidget_itemSelectionChanged();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
