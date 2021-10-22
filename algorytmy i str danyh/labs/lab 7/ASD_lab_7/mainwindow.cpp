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
    case 65546:
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

    tableWidget->item(i,0)->setText(QString::number(BubbleSort(startVect)));
    tableWidget->item(i,1)->setText(QString::number(SelectionSort(startVect)));
    tableWidget->item(i,2)->setText(QString::number(ShellSort(startVect)));
    tableWidget->item(i,3)->setText(QString::number(QuickSort(startVect)));
    tableWidget->item(i,4)->setText(QString::number(MergeSort(startVect)));
    tableWidget->item(i,5)->setText(QString::number(CountingSort(startVect)));
}

void MainWindow::MySlot()
{
    QPushButton* btn = (QPushButton*)sender();
    if(btn->text() == "Start")
    {
        std::vector<int> sizes = {1024, 4096, 16384,65546, 262144, 1048576, 4194304};
        for(const auto& i : sizes){
            SortVector(i,ui->tableWidget);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

