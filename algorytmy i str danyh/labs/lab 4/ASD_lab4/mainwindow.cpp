#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextEdit>
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


void merge(int* array,const int left,const int mid,const int right,QTextEdit* textEdit, int count)
{
    const int  subArrayOneCount = mid - left + 1;
    const int subArrayTwoCount = right - mid;


    int *leftArray = new int[subArrayOneCount],
         *rightArray = new int[subArrayTwoCount];


    for (int i = 0; i < subArrayOneCount; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwoCount; j++)
        rightArray[j] = array[mid + 1 + j];

    int indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    // Merge
    while (indexOfSubArrayOne < subArrayOneCount && indexOfSubArrayTwo < subArrayTwoCount) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOneCount) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwoCount) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    textEdit->append("");

    QString result = "";
    if(array){
        for (int i = 0; i < count; i++ ) {
            result += QString::number(array[i]);
            if(i != count-1){
                result += ", ";
            }
        }
    }
    textEdit->append(result);

    delete [] leftArray;
    delete [] rightArray;
}


void mergeSort(int* array, const int begin,const int  end, QTextEdit* textEdit, int count)
{
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid, textEdit, count);
    mergeSort(array, mid + 1, end, textEdit, count);
    merge(array, begin, mid, end, textEdit, count);
}




void MainWindow::MySlot(){
    QPushButton* btn = (QPushButton*)sender();
    if(btn->text() == "Clear"){
        ui->lineEdit_enter->clear();
        ui->lineEdit_task->clear();
        ui->textEdit_steps->clear();
        ui->lineEdit_result->clear();
    }
    else if(btn->text() == "Random init"){
        ui->lineEdit_enter->clear();
        ui->lineEdit_task->clear();
        ui->textEdit_steps->clear();
        ui->lineEdit_result->clear();
        srand(time(NULL));
        QString str_enter = "";
        int count = (rand() % 10) + 5;
        for (int i = 0; i < count; i++) {
            int rand_val = (rand() % 30);

            str_enter += QString::number(rand_val);
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

        int* array = new int[count_1];

        if(!text.isEmpty()){
            QStringList valuestr = text.split(',');
            for(int j = 0; j < count_1; j++){
                if(!valuestr[j].isEmpty()){
                    bool ok;
                    int value = valuestr[j].toInt(&ok);
                    if(ok){
                        array[j] = value;
                    }else QMessageBox::warning(NULL,"Warning!","Enter the numbers and comas!");
                }
            }
        }else QMessageBox::warning(NULL,"Warning!","Enter the array");

        // task
        int count_mod3 = 0;
        for (int i = 0; i < count_1; i++) {
            if(array[i] % 3 == 0) count_mod3++;
        }
        int count_2 = count_1 - count_mod3;

        int* array_2 = new int[count_2];


        int index = 0;
        for (int i = 0; i < count_1; i++) {
            if(array[i] % 3 != 0){
                array_2[index] = array[i]*array[i];
                index++;
            }
        }

        QString result = "";
        if(array_2){
            for (int i = 0; i < count_2; i++ ) {
                result += QString::number(array_2[i]);
                if(i != count_2-1){
                    result += ", ";
                }
            }
        }
        ui->lineEdit_task->setText(result);

        //Merge sort
        mergeSort(array_2,0,count_2-1, ui->textEdit_steps,count_2);

        result = "";
        if(array_2){
             for (int i = 0; i < count_2; i++ ) {
                 result += QString::number(array_2[i]);
                 if(i != count_2-1){
                    result += ", ";
                 }
             }
        }
        ui->lineEdit_result->setText(result);

        delete [] array;
        delete [] array_2;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

