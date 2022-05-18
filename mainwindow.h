#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:


private slots:


    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_2_clicked();

private:
    bool init = false;
    int table_size = 3;
void resizeEvent(QResizeEvent*);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
