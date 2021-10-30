#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <ctime>
#include <vector>

std::vector<int> g_vect;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_init,SIGNAL(clicked()),this,SLOT(MySlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MySlot()
{
    QPushButton* btn = (QPushButton*)sender();
    if(btn->text()=="Start"){
        for(size_t i = 0; i < g_vect.size(); ++i){
            if(g_vect[i] % 5 == 0){
                ui->textEdit_result->append("Element found: index = " + QString::number(i+1) + " ;");
            }
        }
    }else if(btn->text()== "Clear"){
        ui->textEdit->clear();
        ui->textEdit_result->clear();
    }else if(btn->text() == "Random input"){
        ui->textEdit->clear();
        ui->textEdit_result->clear();
        g_vect.clear();
        srand(time(nullptr));
        for(auto i = 0; i < ui->spinBox->value(); ++i){
            g_vect.push_back(rand() % 500);
        }
        int iter = 0;
        int iterComa = 0;
        QString line;
        for (const auto& a : g_vect) {
            line += QString::number(a);
            if(iterComa != g_vect.size()-1){
                line += ", ";
            }
            if(iter == 14 || iter == g_vect.size()-1){
                ui->textEdit->append(line);
                line = "";
            }
            iter++;
            iterComa++;
        }
    }
}

