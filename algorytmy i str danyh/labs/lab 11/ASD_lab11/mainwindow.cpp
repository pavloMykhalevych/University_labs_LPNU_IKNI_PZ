#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
    ui->textEdit->setText("These modules was hard");
    ui->textEdit_text_2->setText("It was hard to understand");
}

// Removes unnecessary spaces.
std::string RemoveSpaces(std::string myString){
    for (size_t i = 1; i <= myString.size(); ++i) {
        if (myString[i - 1] == ' ' && (myString[i] == ' ' || myString[i] == '\0')) {
            myString.erase(myString.begin() + (i - 1));
            myString.shrink_to_fit();
            i--;
        }
    }
    return myString;
}

void MainWindow::MySlot()
{
    QPushButton* btn = (QPushButton *) sender();
    if(btn->text() == "Start"){
        auto begin = std::chrono::high_resolution_clock::now();
        if(ui->textEdit->toPlainText() == "" || ui->textEdit_text_2->toPlainText() == ""){
            QMessageBox::information(nullptr,"No input data","Enter text 1 and text 2!");
            return;
        }
        QString line = ui->textEdit->toPlainText();
        QString lowerline = line.toLower();
        QStringList list = QString::fromStdString(RemoveSpaces(lowerline.toStdString())).split(' ');

        int sizeSum = 0;
        for (int i = 0;i < list.size(); i++) {
            sizeSum += list[i].size();
        }
        auto wordSize = sizeSum/list.size();
        ui->lineEdit_size->setText(QString::number(wordSize));

        QString word;
        int index;

        for (int i = 0;i < list.size(); i++) {
            if(list[i].size() == wordSize){
                word = list[i];
                index = i;
                ui->lineEdit_word->setText(word);
                ui->lineEdit_word_idx->setText(QString::number(index+1));
                break;
            }
        }

        word = " " + word + " ";

        QString line_2 = " " + ui->textEdit_text_2->toPlainText() + " ";
        QString lowerline_2 = line_2.toLower();
        QString strlowerline_2 = QString::fromStdString(RemoveSpaces(lowerline_2.toStdString())) + " ";

        std::vector<int> table;

        int i = 0;
        int j = 1;
        table.push_back(0);
        bool flag = false;
        while(table.size() != word.size())
        {
            if(word[i] == word[j])
            {
                table.push_back(i+1);
                i++;
                j++;
                continue;
            }
            else
            {
                if(!i) {table.push_back(0); j++;}
                else i = table[i-1];
            }
        }
        int d = 1;
        int spaceCount = 0;
        for (i = 0, j = 0;j < word.size() && i < strlowerline_2.size(); ) {
            if(strlowerline_2[i] == ' '){
                spaceCount++;
            }
            if(d != word.size()){

                if(word[j] == strlowerline_2[i]){
                    i++;
                    j++;
                    d++;
                }else{
                    i += d-table[d-1];
                    j = 0;
                    d = 1;
                }

            }else if(d == word.size()){
                flag = true;
                break;
            }
        }

        if(!flag){
            ui->lineEdit_word_2_idx->setText("Element not found");
        }else{
            ui->lineEdit_word_2_idx->setText(QString::number(spaceCount));
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        ui->lineEdit_task_time->setText(QString::number(elapsed.count()));
    }else if(btn->text() == "Clear"){
        ui->textEdit->clear();
        ui->textEdit_text_2->clear();
        ui->lineEdit_size->clear();
        ui->lineEdit_word_2_idx->clear();
        ui->lineEdit_word->clear();
        ui->lineEdit_word_idx->clear();
        ui->lineEdit_find_time->clear();
        ui->lineEdit_task_time->clear();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

