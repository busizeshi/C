#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QProgressBar;
class QSpinBox;
class QFontComboBox;
class QActionGroup;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel *labFile;
    QLabel *labInfo;
    QProgressBar *progressBar1;
    QSpinBox *spinFontSize;
    QFontComboBox *comboFontName;
    QActionGroup *actionGroup;
    void buildUI();
    void buildSignalSlots();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_fontSize_changed(int fontSize);
    void do_fontSelected(const QFont &font);

    void on_actFont_Bold_triggered();

    void on_actFont_Bold_triggered(bool checked);

    void on_actFont_Italic_triggered(bool checked);

    void on_actFont_UnderLine_triggered(bool checked);

    void on_actFile_Save_triggered();

    void on_actSys_ToggleText_triggered(bool checked);

    void on_plainTextEdit_copyAvailable(bool b);

    void on_plainTextEdit_selectionChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
