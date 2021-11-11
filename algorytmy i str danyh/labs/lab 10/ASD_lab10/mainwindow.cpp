#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MySlot()
{
    QPushButton* btn = (QPushButton *) sender();
    if(btn->text() == "Start"){

    }else if(btn->text() == "Clear"){
        ui->textEdit->clear();
        ui->textEdit_text_2->clear();
        ui->lineEdit_rword->clear();
        ui->lineEdit_rword_idx->clear();
        ui->lineEdit_word->clear();
        ui->lineEdit_word_idx->clear();
    }
}

