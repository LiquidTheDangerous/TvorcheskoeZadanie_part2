#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFormLayout>
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include "gauss.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


//Действия, если количество неизвестных изменилось
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    //Изменение количества строк и столбцов
    this->ui->tableWidget->setRowCount(arg1);
    this->ui->tableWidget->setColumnCount(arg1 + 1);

    QStringList header;
    //Изменения заголовка строкам
    for (int i = 1; i <= arg1;++i)
    {
        header << QString::number(i);
    };
    header<<"=";
    this->ui->tableWidget->setHorizontalHeaderLabels(header);

    this->table_size = arg1;

    auto s2 = this->ui->tableWidget->geometry();
    //Масштабирование
    this->ui->tableWidget->verticalHeader()->setMinimumSectionSize(s2.height()/(this->table_size) - 7);
    this->ui->tableWidget->verticalHeader()->setDefaultSectionSize(s2.height()/(this->table_size) - 7);
    this->ui->tableWidget->horizontalHeader()->setMinimumSectionSize(s2.width()/(this->table_size+1) - 7);
    this->ui->tableWidget->horizontalHeader()->setDefaultSectionSize(s2.width()/(this->table_size+1) - 7);
}
//Масштабирование при изменении размеров окна
void MainWindow::resizeEvent(QResizeEvent * e)
{
    if (this->init)
    {
        auto s2 = this->ui->tableWidget->size();
        this->ui->tableWidget->verticalHeader()->setMinimumSectionSize(s2.height()/(this->table_size) -7);
        this->ui->tableWidget->verticalHeader()->setDefaultSectionSize(s2.height()/(this->table_size) - 7) ;
        this->ui->tableWidget->horizontalHeader()->setMinimumSectionSize(s2.width()/(this->table_size+1) - 7);
        this->ui->tableWidget->horizontalHeader()->setDefaultSectionSize(s2.width()/(this->table_size+1) - 7);
    }
    this->init = true;
}




//Кнопка "Расчитать"
void MainWindow::on_pushButton_2_clicked()
{
    this->ui->textBrowser->clear();
    std::vector<std::vector<double>> matrix(this->table_size,std::vector<double>(this->table_size+1));
    //Проверка на корректность
    //и заполнение марицы
    for (int i = 0; i < this->table_size; ++i)
    {

        for (int j = 0; j < this->table_size+1;++j)
        {
            QTableWidgetItem *dataItem = ui->tableWidget->item(i, j);
            if (!dataItem)
            {

                QMessageBox::warning(this,"Warning!",tr("Вы ввели не все значения!\nОбратите внимание на элемент(%1;%2)").arg(i + 1).arg(j + 1));
                return;
            }
            bool conversionOk = false;
            double value =  ui->tableWidget->item(i,j)->text().toDouble(&conversionOk);
            if (conversionOk)
            {
                matrix[i][j] = value;
            }
            else
            {
                QMessageBox::warning(this,"Warning!",tr("Некорректное значение!\nОбратите внимание на элемент(%1;%2)").arg(i + 1).arg(j + 1));
                return;
            }
        }
    }

    //Решение задачи
    gauss task(matrix);
    std::vector<double> roots = task.rechnen();
    //Если решение существует
    if (task.is_find())
    {
        //Вывод корней
        for(int i = 0; i < roots.size();++i)
        {
            this->ui->textBrowser->append(QString("\tX%1 = %2").arg(i + 1).arg(roots[i]));
        }
    }
    else
    {
        //Иначе - вывод сообщения, что система не имеет решения
        this->ui->textBrowser->setText(QString("Система не имеет решений"));
    }
}

