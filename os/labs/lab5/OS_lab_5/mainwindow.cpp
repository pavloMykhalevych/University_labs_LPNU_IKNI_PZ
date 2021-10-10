#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <iostream>
#include <thread>
#include <math.h>
#include <ctime>
#include <mutex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_suspend,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_resume,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_kill,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_killall,SIGNAL(clicked()),this,SLOT(MySlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
std::mutex mu;
int sum = 0;
int index = 0;
std::vector<int> array(10000,0);
//std::vector<std::thread> mythreads;

void ArraySum(int start, int count){


    for(int i = start; i< count; i++){
        if(i == 0){
            array[i] = 2;
            sum+=array[i];
            continue;
        }
        array[i] = 1/*array[i-1]*i + exp(i)*/;
        sum+=array[i];
        std::cout<<index++<<std::endl;
    }
    std::cout<<"In current thread: sum =" << sum << std::endl;

}

void MainWindow::MySlot(){
QPushButton* btn = (QPushButton*) sender();
    if(btn->text() == "Start"){
        std::thread array_thread[ui->comboBox_thread_count->currentText().toInt()];
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            for(int j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                QTableWidgetItem* item = new QTableWidgetItem;
                item->setText("0");
                item->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(i,j,item);
            }
        }

        for (int i = 0; i<ui->comboBox_thread_count->currentText().toInt(); i++) {
            array_thread[i] = std::thread(ArraySum,(i)*(ui->spinBox_array_size->value()/ui->comboBox_thread_count->currentText().toInt()),
                          (i+1)*(ui->spinBox_array_size->value()/ui->comboBox_thread_count->currentText().toInt()));

            ui->tableWidget->item(i,0)->setText(QString::number(i));
        }
        for (int i = 0; i<ui->comboBox_thread_count->currentText().toInt(); i++) {
            array_thread[i].join();
        }
        std::cout << sum << std::endl;
    }
}

void MainWindow::on_comboBox_thread_count_currentTextChanged(const QString &arg1)
{
    ui->tableWidget->setRowCount(arg1.toInt());
}
