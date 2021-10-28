#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <iostream>
#include <thread>
#include <math.h>
#include <ctime>
#include <chrono>
#include <windows.h>
#include <mutex>
#include <sstream>
#include <QMessageBox>

#define N 16

double GetCpuTime(HANDLE &pi){
    FILETIME createTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;

    if ( GetThreadTimes( pi,
        &createTime, &exitTime, &kernelTime, &userTime ) != -1 )
    {
        SYSTEMTIME userSystemTime;
        if ( FileTimeToSystemTime( &userTime, &userSystemTime ) != -1 )
            return ((double)userSystemTime.wHour * 3600.0 +
            (double)userSystemTime.wMinute * 60.0 +
            (double)userSystemTime.wSecond +
            (double)userSystemTime.wMilliseconds / 1000.0)*1000;
        else return -2;
    } else return -1;
}

std::mutex mu;
HANDLE semaphore;
double time_threads = 0;
int sum = 0;
int myindex = 0;
std::vector<int> array(10000,0);
//std::vector<std::thread> mythreads;
std::vector<HANDLE> myhandle(N, 0);
std::vector<DWORD> mythreadid(N, 0);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i,j,item);
        }
    }

    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_suspend,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_resume,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_kill,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_killall,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_get_sum,SIGNAL(clicked()),this,SLOT(MySlot()));
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(MyTimer()));
    timer->start(100);
}

MainWindow::~MainWindow()
{
    for(size_t i = 0; i < std::size(myhandle); i++){
        DWORD dwCode;
        GetExitCodeThread(myhandle[i],&dwCode);
        if(dwCode == STILL_ACTIVE){
            WaitForSingleObject(myhandle[i], INFINITE);
            CloseHandle(myhandle[i]);
        }
    }
    CloseHandle(semaphore);
    delete ui;
}

void MainWindow::MyTimer(){
    for(int i = 0; i<ui->comboBox_thread_count->currentText().toInt();i++){
        if(ui->tableWidget->item(i,0)->text()!=""){
            ui->tableWidget->item(i,3)->setText(QString::number(GetCpuTime(myhandle[i])));
            DWORD dwCode;
            GetExitCodeThread(myhandle[i],&dwCode);
            if(dwCode != STILL_ACTIVE && ui->tableWidget->item(i,1)->text() != "Killed"){
                ui->tableWidget->item(i,1)->setText("Killed");
            }
        }
    }
    ui->lineEdit->setText(QString::number(time_threads,'f',6)+ " ms" );
}


void ArraySum(int* param)
{
    //Sleep(1000);
    //system("pause");
    const auto start = std::chrono::high_resolution_clock::now();
    for(int i = param[0]; i< param[1]; i++){
        if(i == 0){
            array[i] = 2;
            sum+=array[i];
            continue;
        }
        array[i] = array[i-1]*i + exp(i);
        //sum+=array[i];
        sum+=1;
        std::cout<<myindex++<< " / " << std::endl;
    }
    std::cout<<"In current thread ("<<GetCurrentThreadId()<<"): sum =" << sum << std::endl;
    const auto end = std::chrono::high_resolution_clock::now();
    time_threads += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6;
}

void MutexArraySum(int* param)
{
    mu.lock();
    const auto start = std::chrono::high_resolution_clock::now();
    //Sleep(1000);
    //system("pause");
    for(int i = param[0]; i< param[1]; i++){
        if(i == 0){
            array[i] = 2;
            sum+=array[i];
            continue;
        }
        array[i] = array[i-1]*i + exp(i);
        //sum+=array[i];
        sum+=1;
        std::cout<<myindex++<< " // " << std::endl;
    }
    std::cout<<"In current thread ("<<GetCurrentThreadId()<<")(mutex): sum =" << sum << std::endl;
    const auto end = std::chrono::high_resolution_clock::now();
    time_threads += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6;
    mu.unlock();
}

void SemaphorArraySum(int* param)
{
    WaitForSingleObject(semaphore, INFINITE);
    const auto start = std::chrono::high_resolution_clock::now();
    //Sleep(1000);
    //system("pause");
    for(int i = param[0]; i< param[1]; i++){
        if(i == 0){
            array[i] = 2;
            sum+=array[i];
            continue;
        }
        array[i] = array[i-1]*i + exp(i);
        //sum+=array[i];
        sum+=1;
        std::cout<<myindex++<< " // " << std::endl;
    }
    std::cout<<"In current thread ("<<GetCurrentThreadId()<<")(semaphor): sum =" << sum << std::endl;
    const auto end = std::chrono::high_resolution_clock::now();
    time_threads += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6;
    ReleaseSemaphore(semaphore, 1, nullptr);
}

void MainWindow::MySlot(){
QPushButton* btn = (QPushButton*) sender();
    if(btn->text() == "Start"){
        sum = 0;
        myindex = 0;
        time_threads = 0;
        for(size_t i = 0; i < std::size(myhandle); i++){
            if(myhandle[i] != 0){
            DWORD dwCode;
            GetExitCodeThread(myhandle[i],&dwCode);
            if(dwCode == STILL_ACTIVE){
                WaitForSingleObject(myhandle[i], INFINITE);
                CloseHandle(myhandle[i]);
            }
            }
        }

        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            for(int j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                QTableWidgetItem* item = new QTableWidgetItem;
                item->setText("");
                item->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(i,j,item);
            }
        }
        /*std::thread array_thread[ui->comboBox_thread_count->currentText().toInt()];
        for (int i = 0; i<ui->comboBox_thread_count->currentText().toInt(); i++) {
            array_thread[i] = std::thread(ArraySum,(i)*(ui->spinBox_array_size->value()/ui->comboBox_thread_count->currentText().toInt()),
                          (i+1)*(ui->spinBox_array_size->value()/ui->comboBox_thread_count->currentText().toInt()));

            std::stringstream ss;
            ss << array_thread[i].get_id();
            std::string mystring = ss.str();
            ui->tableWidget->item(i,0)->setText(QString::fromStdString(mystring));
        }
        for (int i = 0; i<ui->comboBox_thread_count->currentText().toInt(); i++) {
            array_thread[i].join();
        }
        std::cout << sum << std::endl;*/

        semaphore = CreateSemaphore(0, 1, 1, nullptr);

        for(int i = 0; i<ui->comboBox_thread_count->currentText().toInt(); i++){
            int* param = new int[2];
            array.resize(ui->spinBox_array_size->value());
            param[0] = (i)*(ui->spinBox_array_size->value()/ui->comboBox_thread_count->currentText().toInt());
            param[1] = (i+1)*(ui->spinBox_array_size->value()/ui->comboBox_thread_count->currentText().toInt());
            if(ui->radioButton->isChecked()){
                myhandle[i] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MutexArraySum, param, 0, &mythreadid[i]);
            }else if(ui->radioButton_semaphor->isChecked()){
                myhandle[i] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&SemaphorArraySum, param, 0, &mythreadid[i]);
            }else{
                myhandle[i] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ArraySum, param, 0, &mythreadid[i]);
            }
            std::stringstream ss;
            ss << mythreadid[i];
            std::string mystring = ss.str();
            ui->tableWidget->item(i,0)->setText(QString::fromStdString(mystring));
            ui->tableWidget->item(i,1)->setText("Running");
            ui->tableWidget->item(i,2)->setText("Normal");
        }
    }else if(btn->text() == "Suspend"){
        if(myhandle[ui->tableWidget->currentRow()] != 0){
        DWORD dwCode;
        GetExitCodeThread(myhandle[ui->tableWidget->currentRow()],&dwCode);
        if(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text() != "Suspended" &&
                ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text() != "Killed" &&
                dwCode == STILL_ACTIVE){
            SuspendThread(myhandle[ui->tableWidget->currentRow()]);
            ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Suspended");
            ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
        }else{
            if(dwCode != STILL_ACTIVE){
                ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Killed");
                ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
            }
            QMessageBox::information(this,"Info","You can't suspend the process!");
        }
        }
    }else if(btn->text() == "Resume"){
        if(myhandle[ui->tableWidget->currentRow()] != 0){
        DWORD dwCode;
        GetExitCodeThread(myhandle[ui->tableWidget->currentRow()],&dwCode);
        if(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text() != "Running" &&
                ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text() != "Killed" &&
                dwCode == STILL_ACTIVE){
            ResumeThread(myhandle[ui->tableWidget->currentRow()]);
            ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Running");
            ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
        }else{
            if(dwCode != STILL_ACTIVE){
                ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Killed");
                ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
            }
            QMessageBox::information(this,"Info","You can't resume the process!");
        }
        }
    }else if(btn->text() == "Kill"){
        if(myhandle[ui->tableWidget->currentRow()] != 0){
        DWORD dwCode;
        GetExitCodeThread(myhandle[ui->tableWidget->currentRow()],&dwCode);
        if(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text() != "Killed" &&
               dwCode == STILL_ACTIVE){
            TerminateThread(myhandle[ui->tableWidget->currentRow()], 0);
            ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Killed");
            ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
        }else{
            if(dwCode != STILL_ACTIVE){
                ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Killed");
                ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
            }
            QMessageBox::information(this,"Info","The process has been killed yet!");
        }
        }
    }else if(btn->text() == "Kill all"){

        for(int i = 0; i < ui->tableWidget->rowCount(); i++){
            if(myhandle[i] != 0){
            DWORD dwCode;
            GetExitCodeThread(myhandle[i],&dwCode);
            if(ui->tableWidget->item(i,1)->text() != "Killed" &&
                    dwCode == STILL_ACTIVE){
                TerminateThread(myhandle[i], 0);
                ui->tableWidget->item(i,1)->setText("Killed");
                ui->tableWidget->item(i,3)->setText(QString::number(GetCpuTime(myhandle[i])));
            }else{
                if(dwCode != STILL_ACTIVE){
                    ui->tableWidget->item(i,1)->setText("Killed");
                    ui->tableWidget->item(i,3)->setText(QString::number(GetCpuTime(myhandle[i])));
                }
            }

        }
        }
    }else if(btn->text() == "Clear"){
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            for(int j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                ui->tableWidget->item(i,j)->setText("");
            }
        }
    }else if(btn->text() == "Get Sum"){
        std::cout << "\nGeneral sum = " << sum << std::endl;
    }
}

void MainWindow::on_comboBox_thread_count_currentTextChanged(const QString &arg1)
{
    //ui->tableWidget->setRowCount(arg1.toInt());
    for(size_t i = 0; i < std::size(myhandle); i++){
        if(myhandle[i] != 0){
        DWORD dwCode;
        GetExitCodeThread(myhandle[i],&dwCode);
        if(dwCode == STILL_ACTIVE){
            WaitForSingleObject(myhandle[i], INFINITE);
            CloseHandle(myhandle[i]);
        }
        }
    }
}

void MainWindow::on_comboBox_priority_currentTextChanged(const QString &arg1)
{
    switch(ui->comboBox_priority->currentIndex()){
    case 0:
        SetThreadPriority(myhandle[ui->tableWidget->currentRow()],THREAD_PRIORITY_TIME_CRITICAL);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
        break;
    case 1:
        SetThreadPriority(myhandle[ui->tableWidget->currentRow()],THREAD_PRIORITY_HIGHEST);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
        break;
    case 2:
        SetThreadPriority(myhandle[ui->tableWidget->currentRow()],THREAD_PRIORITY_ABOVE_NORMAL);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
        break;
    case 3:
        SetThreadPriority(myhandle[ui->tableWidget->currentRow()],THREAD_PRIORITY_NORMAL);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
        break;
    case 4:
        SetThreadPriority(myhandle[ui->tableWidget->currentRow()],THREAD_PRIORITY_BELOW_NORMAL);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
        break;
    case 5:
        SetThreadPriority(myhandle[ui->tableWidget->currentRow()],THREAD_PRIORITY_IDLE);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(myhandle[ui->tableWidget->currentRow()])));
        break;
    }
}
