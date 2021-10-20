#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
}

void MainWindow::SortVector(int size)
{
    std::vector<int> startVect(size,0);
    srand(time(nullptr));
    for (auto& i : startVect) {
        i = rand()%10001;
    }
    BubbleSort(startVect);
    SelectionSort(startVect);
    ShellSort(startVect);
    QuickSort(startVect);
    MergeSort(startVect);
    CountingSort(startVect);
}

void MainWindow::MySlot()
{
    QPushButton* btn = (QPushButton*)sender();
    if(btn->text() == "Start")
    {
        std::vector<int> sizes = {1024, 4096, 16384,65546, 262144, 1048576, 4194304};
        for(const auto& i : sizes){
            SortVector(i);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

