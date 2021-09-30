#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#include <cmath>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_init,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::MySlot()
{

    QPushButton* btn = (QPushButton*)sender();
    if(btn->text() == "Clear"){
        for(int i = 0; i < ui->tableWidget_enter->rowCount(); i++)
            {
                for(int j = 0; j < ui->tableWidget_enter->columnCount(); j++)
                {
                    ui->tableWidget_enter->item(i,j)->setText("");
                    delete ui->tableWidget_enter->item(i,j);
                }
            }

        for(int i = 0; i < ui->tableWidget_result->rowCount(); i++)
            {
                for(int j = 0; j < ui->tableWidget_result->columnCount(); j++)
                {
                    ui->tableWidget_result->item(i,j)->setText("");
                    delete ui->tableWidget_enter->item(i,j);
                }
            }
        ui->textEdit->clear();
        ui->spinBox_column->clear();
        ui->spinBox_column->setValue(ui->spinBox_column->minimum());
        ui->spinBox_row->clear();
        ui->spinBox_row->setValue(ui->spinBox_row->minimum());

    }else if (btn->text() == "Start"){
        ui->textEdit->clear();
        int row_count = ui->tableWidget_enter->rowCount();
        int column_count = ui->tableWidget_enter->columnCount();
        double** mas = new double*[row_count];
        for(int i = 0; i < row_count; i++)
        {
            mas[i] = new double[column_count];
        }

        //Task
        for(int i = 0; i < row_count; i++)
        {
            double max = 0;
            int maxCol = 0;
            for(int j = 0; j < column_count; j++)
            {
                mas[i][j] = ui->tableWidget_enter->item(i,j)->text().toDouble();
                if(mas[i][j] > max){
                    max = mas[i][j];
                    maxCol = j;
                }
            }
            mas[i][maxCol] = pow(mas[i][maxCol],1.0/3);
        }
        for(int i = 0; i < row_count; i++)
        {
            QString strRow = "";
            for(int j = 0; j < column_count; j++)
            {
                strRow += QString::number(mas[i][j],'f',1) + "  ";
            }
            ui->textEdit->append(strRow);
        }
        // Selection sort
        for(int i = 0; i < row_count-1; i++)
        {
            int min_ind = i;
            for (int k = i+1; k < row_count; k++) {
                if(mas[k][0]<mas[min_ind][0]){
                    min_ind = k;
                }
            }
            if(min_ind != i){
                for(int j = 0; j < column_count; j++){
                    double temp = mas[i][j];
                    mas[i][j] = mas[min_ind][j];
                    mas[min_ind][j] = temp;
                }
            }
            ui->textEdit->append("");
            ui->textEdit->append("");
            ui->textEdit->append("Step " + QString::number(i+1)+":");
            ui->textEdit->append("");
            for(int i = 0; i < row_count; i++)
            {
                QString strRow = "";
                for(int j = 0; j < column_count; j++)
                {
                    strRow += QString::number(mas[i][j],'f',1) + "  ";
                }
                ui->textEdit->append(strRow);
            }
        }

        for(int i = 0; i < row_count; i++)
        {
            for(int j = 0; j < column_count; j++)
            {
                ui->tableWidget_result->item(i,j)->setText(QString::number(mas[i][j],'f',1));
            }

        }

        for(int i = 0; i < row_count; i++)
        {
            delete [] mas[i];
        }
        delete [] mas;
    }else if (btn->text() == "Random init"){
        srand(time(NULL));
        for(int i = 0; i < ui->tableWidget_enter->rowCount(); i++)
            {
                for(int j = 0; j < ui->tableWidget_enter->columnCount(); j++)
                {
                    QTableWidgetItem* item = new QTableWidgetItem;
                    double rand_val = (rand() % 200) / 2.3;
                    item->setText(QString::number(rand_val,'f',1));
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->tableWidget_enter->setItem(i,j,item);
                }
            }

        for(int i = 0; i < ui->tableWidget_result->rowCount(); i++)
            {
                for(int j = 0; j < ui->tableWidget_result->columnCount(); j++)
                {
                    QTableWidgetItem* item = new QTableWidgetItem;
                    item->setText("");
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->tableWidget_result->setItem(i,j,item);
                }
            }
    }
}

void MainWindow::on_spinBox_row_valueChanged(int arg1)
{
    ui->tableWidget_enter->setRowCount(arg1);
    ui->tableWidget_result->setRowCount(arg1);

}

void MainWindow::on_spinBox_column_valueChanged(int arg1)
{
    ui->tableWidget_enter->setColumnCount(arg1);
    ui->tableWidget_result->setColumnCount(arg1);

}
