#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->tableWidget);
    ui->tableWidget->setColumnWidth(0,50);
    int widthToSet = (this->width() - 290) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    ui->tableWidget->setColumnWidth(1,widthToSet);
    ui->tableWidget->setColumnWidth(2,widthToSet);
    ui->tableWidget->setColumnWidth(3,120);
    ui->tableWidget->setColumnWidth(4,widthToSet);
    ui->tableWidget->setColumnWidth(5,120-3);

    for (auto i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (auto j = 0; j < ui->tableWidget->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i,j,item);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

