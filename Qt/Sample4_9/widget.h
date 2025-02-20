#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnIniItems_clicked();

    void on_btnIni2_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox2_currentIndexChanged(int index);

    void on_btnClearItems_clicked();

    void on_chkBoxEditable_clicked(bool checked);

    void on_btnClearText_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
