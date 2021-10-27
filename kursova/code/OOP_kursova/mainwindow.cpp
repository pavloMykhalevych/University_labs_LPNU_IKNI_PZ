#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStringList"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->stackedWidget);
    ui->stackedWidget->insertWidget(0,ui->tableWidget);
    ui->stackedWidget->insertWidget(1,ui->tableWidget_2);

    ui->tableWidget->horizontalHeader()->setVisible(true);
    ui->tableWidget_2->horizontalHeader()->setVisible(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ui->stackedWidget->setCurrentIndex(0);

    ui->tableWidget->setColumnWidth(0,50);
    int widthToSet = (this->width() - 340) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    ui->tableWidget->setColumnWidth(1,widthToSet);
    ui->tableWidget->setColumnWidth(2,widthToSet);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,widthToSet);
    ui->tableWidget->setColumnWidth(5,140-3);

    for (auto i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (auto j = 0; j < ui->tableWidget->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i,j,item);
        }
    }
    ui->tableWidget_2->setColumnWidth(0,50);
    int widthToSet_2 = (this->width() - 340) / 3;
    if(widthToSet_2 < 150){
        widthToSet_2 = 150;
    }
    ui->tableWidget_2->setColumnWidth(1,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(2,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(3,150);
    ui->tableWidget_2->setColumnWidth(4,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(5,140-3);

    for (auto i = 0; i < ui->tableWidget_2->rowCount(); i++) {
        for (auto j = 0; j < ui->tableWidget_2->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(i,j,item);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionEdit_table_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->actionAdd->setVisible(true);
    ui->actionAdd->setEnabled(true);
    ui->actionBack_to_table->setVisible(true);
    ui->actionBack_to_table->setEnabled(true);
    ui->actionEdit_table->setVisible(false);
    ui->actionEdit_table->setEnabled(false);
    ui->actionRead_from_file->setVisible(false);
    ui->actionRead_from_file->setEnabled(false);
    ui->actionWrite_to_file->setVisible(false);
    ui->actionWrite_to_file->setEnabled(false);
}

void MainWindow::on_actionBack_to_table_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->actionAdd->setVisible(false);
    ui->actionAdd->setEnabled(false);
    ui->actionBack_to_table->setVisible(false);
    ui->actionBack_to_table->setEnabled(false);
    ui->actionEdit_table->setVisible(true);
    ui->actionEdit_table->setEnabled(true);
    ui->actionRead_from_file->setVisible(true);
    ui->actionRead_from_file->setEnabled(true);
    ui->actionWrite_to_file->setVisible(true);
    ui->actionWrite_to_file->setEnabled(true);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    int widthToSet = (this->width() - 340) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    ui->tableWidget->setColumnWidth(1,widthToSet);
    ui->tableWidget->setColumnWidth(2,widthToSet);
    ui->tableWidget->setColumnWidth(4,widthToSet);

    int widthToSet_2 = (this->width() - 340) / 3;
    if(widthToSet_2 < 150){
        widthToSet_2 = 150;
    }
    ui->tableWidget_2->setColumnWidth(1,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(2,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(4,widthToSet_2);
}

