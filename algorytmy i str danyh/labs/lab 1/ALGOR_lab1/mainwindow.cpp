#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_sort,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_init,SIGNAL(clicked()),this,SLOT(MySlot()));
}

void MainWindow::MySlot(){
    QPushButton* btn = (QPushButton*)sender();
    if(btn->text() == "Очистити"){
        ui->lineEdit_array_1->clear();
        ui->lineEdit_array_2->clear();
        ui->textEdit_steps->clear();
        ui->lineEdit_result->clear();
    }else if(btn->text() == "Ініціалізація"){
        ui->lineEdit_array_1->clear();
        ui->lineEdit_array_2->clear();
        ui->textEdit_steps->clear();
        ui->lineEdit_result->clear();
        srand(time(NULL));
        QString str_enter = "";
        int count = (rand() % 7) + 5;
        for (int i = 0; i < count; i++) {
            int rand_val = (rand() % 100);

            str_enter += QString::number(rand_val);
            if(i != count-1){
                str_enter += ", ";
            }
        }
        ui->lineEdit_array_1->setText(str_enter);

        str_enter = "";
        count = (rand() % 7) + 5;
        for (int i = 0; i < count; i++) {
            int rand_val = (rand() % 100);

            str_enter += QString::number(rand_val);
            if(i != count-1){
                str_enter += ", ";
            }
        }
        ui->lineEdit_array_2->setText(str_enter);
    }
    else if(btn->text() == "Відсортувати"){
        QString text = ui->lineEdit_array_1->text();
        int count_1 = 0;
        int count_2 = 0;
        if(!text.isEmpty()){
            QStringList valuestr = text.split(',');
            count_1 = valuestr.size();
        }else QMessageBox::warning(NULL,"Warning!","Enter the array");
        text = ui->lineEdit_array_2->text();
        if(!text.isEmpty()){
            QStringList valuestr = text.split(',');
            count_2 = valuestr.size();
        }else QMessageBox::warning(NULL,"Warning!","Enter the array");
        int* array_1 = new int[count_1]{0};
        int* array_2 = new int[count_2]{0};
        text = ui->lineEdit_array_1->text();
        if(!text.isEmpty()){
            QStringList valuestr = text.split(',');
            //int count = valuestr.size();
            for(int j = 0; j < count_1; j++){
                if(!valuestr[j].isEmpty()){
                    bool ok;
                    int value = valuestr[j].toInt(&ok);
                    if(ok){
                        array_1[j] = value;
                    }else QMessageBox::warning(NULL,"Warning!","Enter the numbers and coma!");
                }
            }
        }
        text = ui->lineEdit_array_2->text();
        if(!text.isEmpty()){
            QStringList valuestr = text.split(',');
            //int count = valuestr.size();
            for(int j = 0; j < count_2; j++){
                if(!valuestr[j].isEmpty()){
                    bool ok;
                    int value = valuestr[j].toInt(&ok);
                    if(ok){
                        array_2[j] = value;
                    }else QMessageBox::warning(NULL,"Warning!","Enter the numbers and coma!");
                }
            }
        }

        int count_3 = 0;

        for (int i = 0; i < count_1; i++) {
            if(array_1[i] % 2 == 0) count_3++;
        }
        for (int i = 0; i < count_2; i++) {
            if(array_2[i] % 2 == 1) count_3++;
        }

        int* array_3 = new int[count_3]{0};
        int index = 0;
        for (int i = 0; i < count_1; i++) {
            if(array_1[i] % 2 == 0){
                array_3[index] = array_1[i];
                index++;
            }
        }
        for (int i = 0; i < count_2; i++) {
            if(array_2[i] % 2 == 1){
                array_3[index] = array_2[i];
                index++;
            }
        }

        BubbleSort(array_3,count_3,ui->textEdit_steps);


        QString result = "";
        if(array_3){
            for (int i = 0; i < count_3; i++ ) {
                result += QString::number(array_3[i]);
                if(i != count_3-1){
                    result += ", ";
                }
            }
        }
        ui->lineEdit_result->setText(result);

        delete [] array_1;
        delete [] array_2;
        delete [] array_3;
    }
}

void MainWindow::BubbleSort(int* arr,int size, QTextEdit* textedit){
        textedit->setPlainText("");
        for (int i = 0; i < size-1; i++){
            bool F = false;

            textedit->append("Step = " + QString::number(i));

            QString result = "";
            if(arr){
                for (int i = 0; i < size; i++ ) {
                    result += QString::number(arr[i]);
                    if(i != size-1){
                        result += ", ";
                    }
                }
            }

            textedit->append(result);

            for (int j = 0; j < size-i-1; j++) {
                if (arr[j] > arr[j+1]) {
                    swap(&arr[j], &arr[j+1]);
                    F = true;
                    QString result = "";
                    if(arr){
                        for (int i = 0; i < size; i++ ) {
                            result += QString::number(arr[i]);
                            if(i != size-1){
                                result += ", ";
                            }
                        }
                    }

                    textedit->append(result);
                }
            }
            if(F == false) break;

        }
}



MainWindow::~MainWindow()
{
    delete ui;
}

