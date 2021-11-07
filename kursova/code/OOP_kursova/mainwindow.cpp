#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStringList"

#include <QMessageBox>

#include "Functions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->stackedWidget);

    ui->stackedWidget->insertWidget(0,ui->tableWidget);
    ui->stackedWidget->insertWidget(1,ui->tableWidget_2);
    ui->stackedWidget->insertWidget(2,ui->tableWidget_same_type);
    ui->stackedWidget->insertWidget(3,ui->tableWidget_most_type);
    ui->stackedWidget->insertWidget(4,ui->tableWidget_sameduration);
    ui->page->setLayout(ui->verticalLayout_number);
    ui->page_2->setLayout(ui->verticalLayout_surname);
    ui->page_3->setLayout(ui->verticalLayout_ph_num);

    ui->tableWidget->horizontalHeader()->setVisible(true);
    ui->tableWidget_2->horizontalHeader()->setVisible(true);
    ui->tableWidget_number->horizontalHeader()->setVisible(true);
    ui->tableWidget_surname->horizontalHeader()->setVisible(true);
    ui->tableWidget_ph_num->horizontalHeader()->setVisible(true);
    ui->tableWidget_same_type->horizontalHeader()->setVisible(true);
    ui->tableWidget_most_type->horizontalHeader()->setVisible(true);
    ui->tableWidget_sameduration->horizontalHeader()->setVisible(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_number->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_surname->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_ph_num->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_same_type->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_most_type->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_sameduration->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

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
    int widthToSet_2 = (this->width() - 290) / 3;
    if(widthToSet_2 < 150){
        widthToSet_2 = 150;
    }
    ui->tableWidget_2->setColumnWidth(0,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(1,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(2,150);
    ui->tableWidget_2->setColumnWidth(3,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(4,140-3);

    for (auto i = 0; i < ui->tableWidget_2->rowCount(); i++) {
        for (auto j = 0; j < ui->tableWidget_2->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(i,j,item);
        }
    }

    ui->tableWidget_number->setColumnWidth(0,50);
    widthToSet = (this->width() - 340) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    ui->tableWidget_number->setColumnWidth(1,widthToSet);
    ui->tableWidget_number->setColumnWidth(2,widthToSet);
    ui->tableWidget_number->setColumnWidth(3,150);
    ui->tableWidget_number->setColumnWidth(4,widthToSet);
    ui->tableWidget_number->setColumnWidth(5,140-3);

    for (auto i = 0; i < ui->tableWidget_number->rowCount(); i++) {
        for (auto j = 0; j < ui->tableWidget_number->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_number->setItem(i,j,item);
        }
    }

    ui->tableWidget_surname->setColumnWidth(0,50);
    widthToSet = (this->width() - 340) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    ui->tableWidget_surname->setColumnWidth(1,widthToSet);
    ui->tableWidget_surname->setColumnWidth(2,widthToSet);
    ui->tableWidget_surname->setColumnWidth(3,150);
    ui->tableWidget_surname->setColumnWidth(4,widthToSet);
    ui->tableWidget_surname->setColumnWidth(5,140-3);

    for (auto i = 0; i < ui->tableWidget_surname->rowCount(); i++) {
        for (auto j = 0; j < ui->tableWidget_surname->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_surname->setItem(i,j,item);
        }
    }

    ui->tableWidget_ph_num->setColumnWidth(0,50);
    widthToSet = (this->width() - 340) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    ui->tableWidget_ph_num->setColumnWidth(1,widthToSet);
    ui->tableWidget_ph_num->setColumnWidth(2,widthToSet);
    ui->tableWidget_ph_num->setColumnWidth(3,150);
    ui->tableWidget_ph_num->setColumnWidth(4,widthToSet);
    ui->tableWidget_ph_num->setColumnWidth(5,140-3);

    for (auto i = 0; i < ui->tableWidget_ph_num->rowCount(); i++) {
        for (auto j = 0; j < ui->tableWidget_ph_num->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_ph_num->setItem(i,j,item);
        }
    }

    ui->tableWidget_sameduration->setColumnWidth(0,50);
    widthToSet = (this->width() - 340) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    ui->tableWidget_sameduration->setColumnWidth(1,widthToSet);
    ui->tableWidget_sameduration->setColumnWidth(2,widthToSet);
    ui->tableWidget_sameduration->setColumnWidth(3,150);
    ui->tableWidget_sameduration->setColumnWidth(4,widthToSet);
    ui->tableWidget_sameduration->setColumnWidth(5,140-3);

    for (auto i = 0; i < ui->tableWidget_sameduration->rowCount(); i++) {
        for (auto j = 0; j < ui->tableWidget_sameduration->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_sameduration->setItem(i,j,item);
        }
    }

    ui->tableWidget_most_type->setColumnWidth(0,50);
    widthToSet = (this->width() - 340) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    ui->tableWidget_most_type->setColumnWidth(1,widthToSet);
    ui->tableWidget_most_type->setColumnWidth(2,widthToSet);
    ui->tableWidget_most_type->setColumnWidth(3,150);
    ui->tableWidget_most_type->setColumnWidth(4,widthToSet);
    ui->tableWidget_most_type->setColumnWidth(5,140-3);

    for (auto i = 0; i < ui->tableWidget_most_type->rowCount(); i++) {
        for (auto j = 0; j < ui->tableWidget_most_type->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_most_type->setItem(i,j,item);
        }
    }

    ui->tableWidget_same_type->setColumnWidth(0,50);
    widthToSet = (this->width() - 340) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    ui->tableWidget_same_type->setColumnWidth(1,widthToSet);
    ui->tableWidget_same_type->setColumnWidth(2,widthToSet);
    ui->tableWidget_same_type->setColumnWidth(3,150);
    ui->tableWidget_same_type->setColumnWidth(4,widthToSet);
    ui->tableWidget_same_type->setColumnWidth(5,140-3);

    for (auto i = 0; i < ui->tableWidget_same_type->rowCount(); i++) {
        for (auto j = 0; j < ui->tableWidget_same_type->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_same_type->setItem(i,j,item);
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

    int widthToSet_2 = (this->width() - 290) / 3;
    if(widthToSet_2 < 150){
        widthToSet_2 = 150;
    }
    ui->tableWidget_2->setColumnWidth(0,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(1,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(3,widthToSet_2);
}

void MainWindow::on_actionGive_number_Get_duration_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->actionAdd->setVisible(false);
    ui->actionAdd->setEnabled(false);
    ui->actionBack_to_table->setVisible(true);
    ui->actionBack_to_table->setEnabled(true);
    ui->actionEdit_table->setVisible(false);
    ui->actionEdit_table->setEnabled(false);
    ui->actionRead_from_file->setVisible(false);
    ui->actionRead_from_file->setEnabled(false);
    ui->actionWrite_to_file->setVisible(false);
    ui->actionWrite_to_file->setEnabled(false);
}

void MainWindow::on_actionGive_surname_triggered()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->actionAdd->setVisible(false);
    ui->actionAdd->setEnabled(false);
    ui->actionBack_to_table->setVisible(true);
    ui->actionBack_to_table->setEnabled(true);
    ui->actionEdit_table->setVisible(false);
    ui->actionEdit_table->setEnabled(false);
    ui->actionRead_from_file->setVisible(false);
    ui->actionRead_from_file->setEnabled(false);
    ui->actionWrite_to_file->setVisible(false);
    ui->actionWrite_to_file->setEnabled(false);
}

void MainWindow::on_actionGive_phone_number_triggered()
{
    ui->stackedWidget->setCurrentIndex(7);
    ui->actionAdd->setVisible(false);
    ui->actionAdd->setEnabled(false);
    ui->actionBack_to_table->setVisible(true);
    ui->actionBack_to_table->setEnabled(true);
    ui->actionEdit_table->setVisible(false);
    ui->actionEdit_table->setEnabled(false);
    ui->actionRead_from_file->setVisible(false);
    ui->actionRead_from_file->setEnabled(false);
    ui->actionWrite_to_file->setVisible(false);
    ui->actionWrite_to_file->setEnabled(false);
}

void MainWindow::on_actionShow_most_used_type_triggered()
{
    try{
        ui->tableWidget_most_type->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(3);
        ui->actionAdd->setVisible(false);
        ui->actionAdd->setEnabled(false);
        ui->actionBack_to_table->setVisible(true);
        ui->actionBack_to_table->setEnabled(true);
        ui->actionEdit_table->setVisible(false);
        ui->actionEdit_table->setEnabled(false);
        ui->actionRead_from_file->setVisible(false);
        ui->actionRead_from_file->setEnabled(false);
        ui->actionWrite_to_file->setVisible(false);
        ui->actionWrite_to_file->setEnabled(false);
        ShowMostType(ui->tableWidget_most_type, SubscriptionVector);
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

void MainWindow::on_actionShow_with_same_duration_triggered()
{
    try{
        ui->tableWidget_sameduration->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(4);
        ui->actionAdd->setVisible(false);
        ui->actionAdd->setEnabled(false);
        ui->actionBack_to_table->setVisible(true);
        ui->actionBack_to_table->setEnabled(true);
        ui->actionEdit_table->setVisible(false);
        ui->actionEdit_table->setEnabled(false);
        ui->actionRead_from_file->setVisible(false);
        ui->actionRead_from_file->setEnabled(false);
        ui->actionWrite_to_file->setVisible(false);
        ui->actionWrite_to_file->setEnabled(false);
        ShowSameDuration(ui->tableWidget_sameduration, SubscriptionVector);
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

void MainWindow::on_pushButton_num_clicked()
{
    try{
        ui->tableWidget_number->setRowCount(1);
        for (auto i = 0; i < ui->tableWidget_2->rowCount(); i++) {
            for (auto j = 0; j < ui->tableWidget_2->columnCount(); j++) {
                ui->tableWidget_number->item(i,j)->setText("");
            }
        }
        bool ok;
        const auto number = ui->lineEdit_number->text().toUInt(&ok);
        if(!ok){
            QMessageBox::warning(NULL,"Wrong input","Please, enter the positive integer number.");
            return;
        }
        for(const auto& subscription : SubscriptionVector){
            if(subscription.GetNumber() == number){
                ui->tableWidget_number << subscription;
            }
        }
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

void MainWindow::on_pushButton_surname_clicked()
{
    try{
        ui->tableWidget_surname->setRowCount(1);
        for (auto i = 0; i < ui->tableWidget_2->rowCount(); i++) {
            for (auto j = 0; j < ui->tableWidget_2->columnCount(); j++) {
                ui->tableWidget_surname->item(i,j)->setText("");
            }
        }
        const auto surname = ui->lineEdit_surname->text().toStdString();
        if(surname.size() > 35 || surname.size() < 3){
            QMessageBox::warning(NULL,"Wrong input","Please, enter the right surname.");
            return;
        }
        for(const auto& subscription : SubscriptionVector){
            if(subscription.GetSurname() == surname){
                ui->tableWidget_surname << subscription;
            }
        }
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

void MainWindow::on_pushButton_ph_num_clicked()
{
    try{
        ui->tableWidget_ph_num->setRowCount(1);
        for (auto i = 0; i < ui->tableWidget_2->rowCount(); i++) {
            for (auto j = 0; j < ui->tableWidget_2->columnCount(); j++) {
                ui->tableWidget_ph_num->item(i,j)->setText("");
            }
        }
        const auto ph_number = ui->lineEdit_ph_num->text().toStdString();
        if(ph_number.size() > 12 || ph_number.size() < 10 || ph_number.size() == 11){
            throw std::runtime_error("The phone number is incorrect!");
            return;
        }
        if(ph_number.size() == 10){
            throw std::runtime_error("Please, start the phone number with 380...");
            return;
        }
        bool ok;
        QString::fromStdString(ph_number).toULongLong(&ok);
        if(!ok){
            throw std::runtime_error("The phone number is incorrect!");
            return;
        }
        for(const auto& subscription : SubscriptionVector){
            if(subscription.GetPhoneNumber() == ph_number){
                ui->tableWidget_ph_num << subscription;
            }
        }
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

void MainWindow::on_actionSimple_First_Half_Day_triggered()
{
    try{
        ui->tableWidget_same_type->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(2);
        ui->actionAdd->setVisible(false);
        ui->actionAdd->setEnabled(false);
        ui->actionBack_to_table->setVisible(true);
        ui->actionBack_to_table->setEnabled(true);
        ui->actionEdit_table->setVisible(false);
        ui->actionEdit_table->setEnabled(false);
        ui->actionRead_from_file->setVisible(false);
        ui->actionRead_from_file->setEnabled(false);
        ui->actionWrite_to_file->setVisible(false);
        ui->actionWrite_to_file->setEnabled(false);
        ShowSameType(ui->tableWidget_same_type, SubscriptionVector, SubscriptionType::SimpleFirstHalfDay);
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

void MainWindow::on_actionSimple_Full_Day_triggered()
{
    try{
        ui->tableWidget_same_type->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(2);
        ui->actionAdd->setVisible(false);
        ui->actionAdd->setEnabled(false);
        ui->actionBack_to_table->setVisible(true);
        ui->actionBack_to_table->setEnabled(true);
        ui->actionEdit_table->setVisible(false);
        ui->actionEdit_table->setEnabled(false);
        ui->actionRead_from_file->setVisible(false);
        ui->actionRead_from_file->setEnabled(false);
        ui->actionWrite_to_file->setVisible(false);
        ui->actionWrite_to_file->setEnabled(false);
        ShowSameType(ui->tableWidget_same_type, SubscriptionVector, SubscriptionType::SimpleFullDay);
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

void MainWindow::on_actionLux_Full_Day_triggered()
{
    try{
        ui->tableWidget_same_type->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(2);
        ui->actionAdd->setVisible(false);
        ui->actionAdd->setEnabled(false);
        ui->actionBack_to_table->setVisible(true);
        ui->actionBack_to_table->setEnabled(true);
        ui->actionEdit_table->setVisible(false);
        ui->actionEdit_table->setEnabled(false);
        ui->actionRead_from_file->setVisible(false);
        ui->actionRead_from_file->setEnabled(false);
        ui->actionWrite_to_file->setVisible(false);
        ui->actionWrite_to_file->setEnabled(false);
        ShowSameType(ui->tableWidget_same_type, SubscriptionVector, SubscriptionType::LuxFullDay);
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

void MainWindow::on_actionSuper_Lux_Full_Day_triggered()
{
    try {
        ui->tableWidget_same_type->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(2);
        ui->actionAdd->setVisible(false);
        ui->actionAdd->setEnabled(false);
        ui->actionBack_to_table->setVisible(true);
        ui->actionBack_to_table->setEnabled(true);
        ui->actionEdit_table->setVisible(false);
        ui->actionEdit_table->setEnabled(false);
        ui->actionRead_from_file->setVisible(false);
        ui->actionRead_from_file->setEnabled(false);
        ui->actionWrite_to_file->setVisible(false);
        ui->actionWrite_to_file->setEnabled(false);
        ShowSameType(ui->tableWidget_same_type, SubscriptionVector, SubscriptionType::SuperLuxFullDay);
    }  catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }
}

void MainWindow::on_actionRead_from_file_triggered()
{
    try{
        "C:\\LPNU\\kursova\\code\\OOP_kursova\\Input.txt" >> SubscriptionVector;
        ui->tableWidget << SubscriptionVector;
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }
}

void MainWindow::on_actionWrite_to_file_triggered()
{
    try{
        "C:\\LPNU\\kursova\\code\\OOP_kursova\\Output.txt" << SubscriptionVector;
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }
}

void MainWindow::on_actionAdd_triggered()
{
    try{
        ui->tableWidget_2 >> SubscriptionVector;
        ui->tableWidget << SubscriptionVector.back();
        for (auto i = 0; i < ui->tableWidget_2->rowCount(); i++) {
            for (auto j = 0; j < ui->tableWidget_2->columnCount(); j++) {
                ui->tableWidget_2->item(i,j)->setText("");
            }
        }
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }
}

