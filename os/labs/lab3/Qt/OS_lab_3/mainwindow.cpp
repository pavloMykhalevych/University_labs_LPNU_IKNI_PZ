#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

double GetCpuTime(PROCESS_INFORMATION &pi){
    FILETIME createTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;

    if ( GetProcessTimes( pi.hProcess,
        &createTime, &exitTime, &kernelTime, &userTime ) != -1 )
    {
        SYSTEMTIME userSystemTime;
        if ( FileTimeToSystemTime( &userTime, &userSystemTime ) != -1 )
            return (double)userSystemTime.wHour * 3600.0 +
            (double)userSystemTime.wMinute * 60.0 +
            (double)userSystemTime.wSecond +
            (double)userSystemTime.wMilliseconds / 1000.0;
        else return -2;
    } else return -1;
}

STARTUPINFO si[8];
PROCESS_INFORMATION pi[8];

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

    for(int i = 0; i < 8; i++){
        CloseHandle(pi[i].hThread);
        CloseHandle(pi[i].hProcess);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MySlot()
{

    QPushButton* btn = (QPushButton*) sender();
    if(btn->text() == "Start"){
        int ProcessCount = ui->comboBox_process_count->currentText().toInt();
        int rowCount = ui->spinBox_row_count->value();
        int columnCount = ui->spinBox_column_count->value();

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

        std::wstring cmd  = L"C:\\LPNU\\os\\labs\\lab3\\OS_lab_3\\x64\\Debug\\OS_lab_3 "
                            + std::to_wstring(rowCount) + L" " + std::to_wstring(columnCount);
        for(int i = 0; i < ProcessCount; i++){
            ZeroMemory(&si[i], sizeof(si[i]));
            si[i].cb = sizeof(si[i]);

            ZeroMemory(&pi[i], sizeof(pi[i]));

            CreateProcess(NULL,&(cmd[0]),NULL,NULL,true, REALTIME_PRIORITY_CLASS |
                            CREATE_NEW_CONSOLE,NULL,NULL,&si[i],&pi[i]);

            ui->tableWidget->item(i,0)->setText(QString::number(pi[i].dwProcessId));
            //ui->tableWidget->item(i,1)->setText("Suspended");
            ui->tableWidget->item(i,1)->setText("Running");
            ui->tableWidget->item(i,2)->setText("High");
            ui->tableWidget->item(i,3)->setText("0");
        }

        //Sleep(1500);

        //for(int i = 0; i < ProcessCount; i++)
        //{
        //    SuspendThread(pi[i].hThread);
        //    ui->tableWidget->item(i,3)->setText(QString::number(GetCpuTime(pi[i])));
        //}

    }else if(btn->text() == "Suspend"){
        DWORD dwCode;
        GetExitCodeProcess(pi[ui->tableWidget->currentRow()].hProcess,&dwCode);
        if(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text() != "Suspended" &&
                ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text() != "Killed" &&
                dwCode == STATUS_PENDING){
            SuspendThread(pi[ui->tableWidget->currentRow()].hThread);
            ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Suspended");
            ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
        }else{
            if(dwCode != STATUS_PENDING){
                ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Killed");
                ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
            }
            QMessageBox::information(this,"Info","You can't suspend the process!");
        }
    }else if(btn->text() == "Resume"){
        DWORD dwCode;
        GetExitCodeProcess(pi[ui->tableWidget->currentRow()].hProcess,&dwCode);
        if(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text() != "Running" &&
                ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text() != "Killed" &&
                dwCode == STATUS_PENDING){
            ResumeThread(pi[ui->tableWidget->currentRow()].hThread);
            ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Running");
            ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
        }else{
            if(dwCode != STATUS_PENDING){
                ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Killed");
                ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
            }
            QMessageBox::information(this,"Info","You can't resume the process!");
        }
    }else if(btn->text() == "Kill"){
        DWORD dwCode;
        GetExitCodeProcess(pi[ui->tableWidget->currentRow()].hProcess,&dwCode);
        if(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text() != "Killed" &&
               dwCode == STATUS_PENDING){
            TerminateThread(pi[ui->tableWidget->currentRow()].hThread, 0);
            ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Killed");
            ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
        }else{
            if(dwCode != STATUS_PENDING){
                ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText("Killed");
                ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
            }
            QMessageBox::information(this,"Info","The process has been killed yet!");
        }
    }else if(btn->text() == "Kill all"){
        for(int i = 0; i < ui->tableWidget->rowCount(); i++){
            DWORD dwCode;
            GetExitCodeProcess(pi[i].hProcess,&dwCode);
            if(ui->tableWidget->item(i,1)->text() != "Killed" &&
                    dwCode == STATUS_PENDING){
                TerminateThread(pi[i].hThread, 0);
                ui->tableWidget->item(i,1)->setText("Killed");
                ui->tableWidget->item(i,3)->setText(QString::number(GetCpuTime(pi[i])));
            }else{
                if(dwCode != STATUS_PENDING){
                    ui->tableWidget->item(i,1)->setText("Killed");
                    ui->tableWidget->item(i,3)->setText(QString::number(GetCpuTime(pi[i])));
                }
            }
        }
    }
}



void MainWindow::on_comboBox_process_count_currentTextChanged(const QString &arg1)
{
    ui->tableWidget->setRowCount(arg1.toInt());
}

void MainWindow::on_comboBox_priority_currentTextChanged(const QString &arg1)
{
    switch(ui->comboBox_priority->currentIndex()){
    case 0:
        SetPriorityClass(pi[ui->tableWidget->currentRow()].hProcess,REALTIME_PRIORITY_CLASS);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
        break;
    case 1:
        SetPriorityClass(pi[ui->tableWidget->currentRow()].hProcess,HIGH_PRIORITY_CLASS);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
        break;
    case 2:
        SetPriorityClass(pi[ui->tableWidget->currentRow()].hProcess,ABOVE_NORMAL_PRIORITY_CLASS);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
        break;
    case 3:
        SetPriorityClass(pi[ui->tableWidget->currentRow()].hProcess,NORMAL_PRIORITY_CLASS);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
        break;
    case 4:
        SetPriorityClass(pi[ui->tableWidget->currentRow()].hProcess,BELOW_NORMAL_PRIORITY_CLASS);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
        break;
    case 5:
        SetPriorityClass(pi[ui->tableWidget->currentRow()].hProcess,IDLE_PRIORITY_CLASS);
        ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->comboBox_priority->currentText());
        ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::number(GetCpuTime(pi[ui->tableWidget->currentRow()])));
        break;
    }
}
