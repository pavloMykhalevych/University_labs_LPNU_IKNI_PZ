#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_init,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
}

void MainWindow::MySlot(){
    QPushButton* btn = (QPushButton*)sender();
    if(btn->text() == "Clear"){
        ui->lineEdit_enter->clear();
        ui->textEdit_steps->clear();
        ui->lineEdit_result->clear();
    }
    else if(btn->text() == "Random init"){
        ui->lineEdit_enter->clear();
        ui->textEdit_steps->clear();
        ui->lineEdit_result->clear();
        srand(time(NULL));
        QString str_enter = "";
        int count = (rand() % 7) + 5;
        for (int i = 0; i < count; i++) {
            double rand_val = (rand() % 100) / 2.3;

            str_enter += QString::number(rand_val,'f',1);
            if(i != count-1){
                str_enter += ", ";
            }
        }
        ui->lineEdit_enter->setText(str_enter);
    }
    else if(btn->text() == "Start"){
        QString text = ui->lineEdit_enter->text();

        int count_1 = 0;

        if(!text.isEmpty()){
            QStringList valuestr = text.split(',');
            count_1 = valuestr.size();
        }

        double* array = new double[count_1];

        if(!text.isEmpty()){
            QStringList valuestr = text.split(',');
            for(int j = 0; j < count_1; j++){
                if(!valuestr[j].isEmpty()){
                    bool ok;
                    double value = valuestr[j].toDouble(&ok);
                    if(ok){
                        array[j] = value;
                    }else QMessageBox::warning(NULL,"Warning!","Enter the numbers and comas!");
                }
            }
        }else QMessageBox::warning(NULL,"Warning!","Enter the array");

        // task
        int max_Index = 0;

        for (int i = 0;i< count_1 ;i++ ) {
            if(array[max_Index] < array[i]){
                max_Index = i;
            }
        }

        //Shell sort
        int start_Index = max_Index + 1;
        int d = (count_1 - start_Index) / 2;
        QString result = "";
        if(array){
            for (int i = 0; i < count_1; i++ ) {
                result += QString::number(array[i],'f',1);
                if(i != count_1-1){
                    result += ", ";
                }
            }
        }

        ui->textEdit_steps->append(result);
        while(d >= 1){
            for (int i = start_Index + d; i < count_1; i++) {
                for (int j = i; j >= start_Index; j -= d ) {
                    int min_Index = j;
                    for (int k = j-d; k >= start_Index; k -= d ) {
                        if(array[k]<array[min_Index]){
                            min_Index = k;
                        }
                    }
                    if(min_Index != j){
                        double tmp = array[min_Index];
                        array[min_Index] = array[j];
                        array[j] = tmp;
                    }
                }

            }
            ui->textEdit_steps->append("");
            ui->textEdit_steps->append("Step d = "+QString::number(d)+" (Max = "+QString::number(array[max_Index],'f',1)+") :");
            QString result = "";
            if(array){
                for (int i = 0; i < count_1; i++ ) {
                    result += QString::number(array[i],'f',1);
                    if(i != count_1-1){
                        result += ", ";
                    }
                }
            }

            ui->textEdit_steps->append(result);
            d /= 2;
        }

        result = "";
        if(array){
            for (int i = 0; i < count_1; i++ ) {
                result += QString::number(array[i],'f',1);
                if(i != count_1-1){
                    result += ", ";
                }
            }
        }
        ui->lineEdit_result->setText(result);

        delete [] array;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

