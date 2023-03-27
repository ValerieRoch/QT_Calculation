#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ctime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox_Pret_stateChanged(int arg1);

    void on_checkBox_Pret_clicked(bool checked);

    void on_lineEdit_Total_returnPressed();

private:
    Ui::MainWindow *ui;

    void  InitWindow  (void);
    void  BlockSpinBox  (void);
    void  UnBlockSpinBox  (void);
    void  Iterration  (void);
};
#endif // MAINWINDOW_H
