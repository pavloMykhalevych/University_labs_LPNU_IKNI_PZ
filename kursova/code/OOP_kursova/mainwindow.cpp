#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->tableWidget);
    ui->tableWidget->setColumnWidth(0,50);
    int widthToSet = this->width() / 5;
    if(widthToSet < 150 || widthToSet > 300){
        ui->tableWidget->setColumnWidth(3,widthToSet);
    }
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,150);
    ui->tableWidget->setColumnWidth(5,150);
    /*std::vector<QString> columnHeaders = {"№","Surname","Name","Phone number","Subscription type","Duration"};
    for (size_t i = 0;i < columnHeaders.size(); i++) {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(columnHeaders[i]);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setHorizontalHeaderItem(i,item);
    }*/
    //ui->tableWidget->header
    //int widthToSet = this->width() / 5;
    //if(widthToSet < 150)
}

MainWindow::~MainWindow()
{
    delete ui;
}

