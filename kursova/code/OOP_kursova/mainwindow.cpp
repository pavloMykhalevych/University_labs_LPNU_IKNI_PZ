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

    // Setting UI
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

    SetTableWidget(ui->tableWidget,this);

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

    SetTableWidget(ui->tableWidget_number,this);

    SetTableWidget(ui->tableWidget_surname,this);

    SetTableWidget(ui->tableWidget_ph_num,this);

    SetTableWidget(ui->tableWidget_sameduration,this);

    SetTableWidget(ui->tableWidget_most_type,this);

    SetTableWidget(ui->tableWidget_same_type,this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Open the widget with editable table.
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

// Go back to table.
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

// Event that resize the table.
void MainWindow::resizeEvent(QResizeEvent *)
{
    int widthToSet_2 = (this->width() - 290) / 3;
    if(widthToSet_2 < 150){
        widthToSet_2 = 150;
    }
    ui->tableWidget_2->setColumnWidth(0,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(1,widthToSet_2);
    ui->tableWidget_2->setColumnWidth(3,widthToSet_2);

    FuncForResizeEvent(ui->tableWidget,this);
    FuncForResizeEvent(ui->tableWidget_most_type,this);
    FuncForResizeEvent(ui->tableWidget_number,this);
    FuncForResizeEvent(ui->tableWidget_ph_num,this);
    FuncForResizeEvent(ui->tableWidget_same_type,this);
    FuncForResizeEvent(ui->tableWidget_sameduration,this);
    FuncForResizeEvent(ui->tableWidget_surname,this);
}

// Open the widget where you give the number and get the info about person with such number.
void MainWindow::on_actionGive_number_Get_duration_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
    BackToTableOff();
}

// Open the widget where you give the surname and get the info about person with such surname.
void MainWindow::on_actionGive_surname_triggered()
{
    ui->stackedWidget->setCurrentIndex(6);
    BackToTableOff();
}

// Open the widget where you give the phone number and get the info about person with such phone number.
void MainWindow::on_actionGive_phone_number_triggered()
{
    ui->stackedWidget->setCurrentIndex(7);
    BackToTableOff();
}

// Show people who have the most used subscription type.
void MainWindow::on_actionShow_most_used_type_triggered()
{
    try{
        ui->tableWidget_most_type->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(3);
        BackToTableOff();
        ShowMostType(ui->tableWidget_most_type, SubscriptionVector);
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

// Show people who have the most used duration.
void MainWindow::on_actionShow_with_same_duration_triggered()
{
    try{
        ui->tableWidget_sameduration->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(4);
        BackToTableOff();
        ShowSameDuration(ui->tableWidget_sameduration, SubscriptionVector);
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

// Show person with the number you give.
void MainWindow::on_pushButton_num_clicked()
{
    try{
        if(SubscriptionVector.empty()){
            QMessageBox::information(NULL,"Info","There is no data.");
            return;
        }
        ui->tableWidget_number->setRowCount(1);
        for (auto i = 0; i < ui->tableWidget_number->rowCount(); i++) {
            for (auto j = 0; j < ui->tableWidget_number->columnCount(); j++) {
                ui->tableWidget_number->item(i,j)->setText("");
            }
        }
        bool ok;
        const auto number = ui->lineEdit_number->text().toUInt(&ok);
        if(!ok){
            QMessageBox::warning(NULL,"Wrong input","Please, enter the positive integer number.");
            return;
        }
        int count = 0;
        for(const auto& subscription : SubscriptionVector){
            if(subscription.GetNumber() == number){
                ui->tableWidget_number << subscription;
                ++count;
            }
        }
        if(count == 0){
            QMessageBox::information(NULL,"Info","There is no person with such number.");
        }
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

// Show people with the surname you give.
void MainWindow::on_pushButton_surname_clicked()
{
    try{
        if(SubscriptionVector.empty()){
            QMessageBox::information(NULL,"Info","There is no data.");
            return;
        }
        ui->tableWidget_surname->setRowCount(1);
        for (auto i = 0; i < ui->tableWidget_surname->rowCount(); i++) {
            for (auto j = 0; j < ui->tableWidget_surname->columnCount(); j++) {
                ui->tableWidget_surname->item(i,j)->setText("");
            }
        }
        auto surname = ui->lineEdit_surname->text().toStdString();
        RemoveSpaces(surname);
        if(surname.size() > 35 || surname.size() < 3){
            QMessageBox::warning(NULL,"Wrong input","Please, enter the right surname.");
            return;
        }
        int count = 0;
        for(const auto& subscription : SubscriptionVector){
            if(subscription.GetSurname() == surname){
                ui->tableWidget_surname << subscription;
                ++count;
            }
        }
        if(count == 0){
            QMessageBox::information(NULL,"Info","There is no person with such surname.");
        }
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

// Show people with the phone number you give.
void MainWindow::on_pushButton_ph_num_clicked()
{
    try{
        if(SubscriptionVector.empty()){
            QMessageBox::information(NULL,"Info","There is no data.");
            return;
        }
        ui->tableWidget_ph_num->setRowCount(1);
        for (auto i = 0; i < ui->tableWidget_surname->rowCount(); i++) {
            for (auto j = 0; j < ui->tableWidget_surname->columnCount(); j++) {
                ui->tableWidget_ph_num->item(i,j)->setText("");
            }
        }
        auto ph_number = ui->lineEdit_ph_num->text().toStdString();
        RemoveSpaces(ph_number);
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
        int count = 0;
        for(const auto& subscription : SubscriptionVector){
            if(subscription.GetPhoneNumber() == ph_number){
                ui->tableWidget_ph_num << subscription;
                ++count;
            }
        }
        if(count == 0){
            QMessageBox::information(NULL,"Info","There is no person with such phone number.");
        }
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

// Show person with the subscription type you pick.
void MainWindow::on_actionSimple_First_Half_Day_triggered()
{
    try{
        ui->tableWidget_same_type->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(2);
        BackToTableOff();
        ShowSameType(ui->tableWidget_same_type, SubscriptionVector, SubscriptionType::SimpleFirstHalfDay);
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

// Show person with the subscription type you pick.
void MainWindow::on_actionSimple_Full_Day_triggered()
{
    try{
        ui->tableWidget_same_type->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(2);
        BackToTableOff();
        ShowSameType(ui->tableWidget_same_type, SubscriptionVector, SubscriptionType::SimpleFullDay);
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

// Show person with the subscription type you pick.
void MainWindow::on_actionLux_Full_Day_triggered()
{
    try{
        ui->tableWidget_same_type->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(2);
        BackToTableOff();
        ShowSameType(ui->tableWidget_same_type, SubscriptionVector, SubscriptionType::LuxFullDay);
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }

}

// Show person with the subscription type you pick.
void MainWindow::on_actionSuper_Lux_Full_Day_triggered()
{
    try {
        ui->tableWidget_same_type->setRowCount(1);
        ui->stackedWidget->setCurrentIndex(2);
        BackToTableOff();
        ShowSameType(ui->tableWidget_same_type, SubscriptionVector, SubscriptionType::SuperLuxFullDay);
    }  catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }
}

// Read the info from file and fill the table.
void MainWindow::on_actionRead_from_file_triggered()
{
    try{
        "C:\\LPNU\\kursova\\code\\OOP_kursova\\Input.txt" >> SubscriptionVector;
        ui->tableWidget << SubscriptionVector;
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }
}

// Write the info from table to file.
void MainWindow::on_actionWrite_to_file_triggered()
{
    try{
        "C:\\LPNU\\kursova\\code\\OOP_kursova\\Output.txt" << SubscriptionVector;
    }catch(const std::exception& exc){
        QMessageBox::warning(NULL,"Error",QString::fromStdString(exc.what()));
    }
}

// Add person you write to table.
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

// Some prosperities needed when you go to additional widgets.
void MainWindow::BackToTableOff()
{
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

