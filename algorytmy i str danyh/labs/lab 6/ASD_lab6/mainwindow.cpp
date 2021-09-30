#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <map>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_init,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
}



MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::MySlot()
{

    QPushButton* btn = (QPushButton*)sender();
    if(btn->text() == "Clear"){
        for(int i = 0; i < ui->tableWidget_enter->rowCount(); i++)
            {
                for(int j = 0; j < ui->tableWidget_enter->columnCount(); j++)
                {
                    ui->tableWidget_enter->item(i,j)->setText("");
                    delete ui->tableWidget_enter->item(i,j);
                }
            }

        for(int i = 0; i < ui->tableWidget_result->rowCount(); i++)
            {
                for(int j = 0; j < ui->tableWidget_result->columnCount(); j++)
                {
                    ui->tableWidget_result->item(i,j)->setText("");
                    delete ui->tableWidget_enter->item(i,j);
                }
            }
        ui->textEdit->clear();
        ui->spinBox_column->clear();
        ui->spinBox_column->setValue(ui->spinBox_column->minimum());
        ui->spinBox_row->clear();
        ui->spinBox_row->setValue(ui->spinBox_row->minimum());

    }else if (btn->text() == "Start"){
        ui->textEdit->clear();
        int row_count = ui->tableWidget_enter->rowCount();
        int column_count = ui->tableWidget_enter->columnCount();
        double** mas = new double*[row_count];
        for(int i = 0; i < row_count; i++)
        {
            mas[i] = new double[column_count];
        }
        double** sort_mas = new double*[row_count];
        for(int i = 0; i < row_count; i++)
        {
            sort_mas[i] = new double[column_count];
        }
        //Task
        double * row_index = new double[row_count]{0};
        double * sort_row_index = new double[row_count]{0};
        for(int i = 0; i < row_count; i++)
        {

            for(int j = 0; j < column_count; j++)
            {
                mas[i][j] = ui->tableWidget_enter->item(i,j)->text().toDouble();
                row_index[i] += mas[i][j];
            }

        }
        for(int i = 0; i < row_count; i++)
        {
            sort_row_index[i] = row_index[i];
        }



        // Count sort

        std::map<double,int> keys_values;
        for(int i = 0; i < row_count; i++)
        {
            keys_values[sort_row_index[i]]++;
        }

        for(auto it : keys_values){
             QString strRow = "";
             strRow += QString::number(it.second) + " - " +QString::number(it.first,'f',1);
             ui->textEdit->append(strRow);
        }

        int ind = 0;
        for(auto it : keys_values){
            double val = it.first;
            int freq = it.second;
            for (int j = 0;j < freq ;j++ ) {
                sort_row_index[ind] = val;
                ind++;
            }
        }
        ui->textEdit->append("");
        for(int i = 0; i < row_count; i++)
        {
            QString strRow = "";
            strRow += QString::number(row_index[i],'f',1) + "    \\    " +QString::number(sort_row_index[i],'f',1);
            ui->textEdit->append(strRow);
        }
        for(int i = 0; i < row_count; i++){

            for (int j = 0; j < row_count ; j++ ) {
                if(static_cast<int>(row_index[i]*10) == static_cast<int>(sort_row_index[j]*10)){

                    for (int k = 0; k < column_count ; k++ ) {
                        sort_mas[j][k] = mas[i][k];
                    }
                    sort_row_index[j] = 0;
                    break;
                }
            }

        }
        ui->textEdit->append("");
        for(int i = 0; i < row_count; i++)
        {
            QString strRow = "";
            strRow += QString::number(row_index[i],'f',1) + "    \\    " +QString::number(sort_row_index[i],'f',1);
            ui->textEdit->append(strRow);
        }


        for(int i = 0; i < row_count; i++)
        {
            for(int j = 0; j < column_count; j++)
            {
                ui->tableWidget_result->item(i,j)->setText(QString::number(sort_mas[i][j],'f',1));
            }

        }

        for(int i = 0; i < row_count; i++)
        {
            delete [] mas[i];
        }
        delete [] mas;
        for(int i = 0; i < row_count; i++)
        {
            delete [] sort_mas[i];
        }
        delete [] sort_mas;
        delete [] row_index;
        delete [] sort_row_index;
    }else if (btn->text() == "Random init"){
        srand(time(NULL));
        for(int i = 0; i < ui->tableWidget_enter->rowCount(); i++)
            {
                for(int j = 0; j < ui->tableWidget_enter->columnCount(); j++)
                {
                    QTableWidgetItem* item = new QTableWidgetItem;
                    double rand_val = static_cast<double>(rand() % 200) / 2.5;
                    item->setText(QString::number(rand_val,'f',1));
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->tableWidget_enter->setItem(i,j,item);
                }
            }

        for(int i = 0; i < ui->tableWidget_result->rowCount(); i++)
            {
                for(int j = 0; j < ui->tableWidget_result->columnCount(); j++)
                {
                    QTableWidgetItem* item = new QTableWidgetItem;
                    item->setText("");
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->tableWidget_result->setItem(i,j,item);
                }
            }
    }
}

void MainWindow::on_spinBox_row_valueChanged(int arg1)
{
    ui->tableWidget_enter->setRowCount(arg1);
    ui->tableWidget_result->setRowCount(arg1);

}

void MainWindow::on_spinBox_column_valueChanged(int arg1)
{
    ui->tableWidget_enter->setColumnCount(arg1);
    ui->tableWidget_result->setColumnCount(arg1);

}
