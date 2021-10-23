#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>

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
    connect(ui->pushButton_start_2,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start_3,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start_4,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start_5,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start_6,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start_7,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start_8,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
}

void MainWindow::SortVector(int size, QTableWidget* tableWidget)
{
    std::vector<int> startVect(size,0);
    srand(time(nullptr));
    for (auto& i : startVect) {
        i = rand()%10001;
    }
    int i = 0;
    switch(size){
    case 1024:
        i = 0;
        break;
    case 4096:
        i = 1;
        break;
    case 16384:
        i = 2;
        break;
    case 65536:
        i = 3;
        break;
    case 262144:
        i = 4;
        break;
    case 1048576:
        i = 5;
        break;
    case 4194304:
        i = 6;
        break;
    }

    tableWidget->item(i,0)->setText(QString::number(BubbleSort(startVect),'f',6));
    tableWidget->item(i,1)->setText(QString::number(SelectionSort(startVect),'f',6));
    tableWidget->item(i,2)->setText(QString::number(ShellSort(startVect),'f',6));
    tableWidget->item(i,3)->setText(QString::number(QuickSort(startVect),'f',6));
    tableWidget->item(i,4)->setText(QString::number(MergeSort(startVect),'f',6));
    tableWidget->item(i,5)->setText(QString::number(CountingSort(startVect),'f',6));
}

void MainWindow::MySlot()
{
    std::vector<int> sizes = {1024, 4096, 16384,65536, 262144, 1048576, 4194304};
    QPushButton* btn = (QPushButton*)sender();
    if(btn->text() == "Start 1024")
    {
        SortVector(sizes[0],ui->tableWidget);

    }else if(btn->text() == "Start 4096")
    {
        SortVector(sizes[1],ui->tableWidget);

    }else if(btn->text() == "Start 16384")
    {
        SortVector(sizes[2],ui->tableWidget);

    }else if(btn->text() == "Start 65536")
    {
        SortVector(sizes[3],ui->tableWidget);

    }else if(btn->text() == "Start 262144")
    {
        SortVector(sizes[4],ui->tableWidget);

    }else if(btn->text() == "Start 1048576")
    {
        SortVector(sizes[5],ui->tableWidget);

    }else if(btn->text() == "Start 4194304")
    {
        SortVector(sizes[6],ui->tableWidget);

    }else if(btn->text() == "Start")
    {
        SortVector(sizes[0],ui->tableWidget);
        SortVector(sizes[1],ui->tableWidget);
        SortVector(sizes[2],ui->tableWidget);
        SortVector(sizes[3],ui->tableWidget);
        SortVector(sizes[4],ui->tableWidget);
        SortVector(sizes[5],ui->tableWidget);
        SortVector(sizes[6],ui->tableWidget);

    }else if(btn->text() == "Clear")
    {
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            {
                for(int j = 0; j < ui->tableWidget->columnCount(); j++)
                {
                    ui->tableWidget->item(i,j)->setText("");
                }
            }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

