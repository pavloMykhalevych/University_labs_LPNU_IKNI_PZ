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
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Removes unnecessary spaces.
std::string RemoveSpaces(std::string myString){
    for (size_t i = 1; i <= myString.size(); ++i) {
//        if(i-1 == 0 && myString[i - 1] == ' '){
//            myString.erase(myString.begin() + (i - 1));
//            myString.shrink_to_fit();
//            i--;
//            continue;
//        }
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
        if(ui->textEdit->toPlainText() == "" || ui->textEdit_text_2->toPlainText() == ""){
            QMessageBox::information(nullptr,"No input data","Enter text 1 and text 2!");
            return;
        }
        QString line = ui->textEdit->toPlainText();
        QString lowerline = line.toLower();
        QStringList list = QString::fromStdString(RemoveSpaces(lowerline.toStdString())).split(' ');

        int minIdx = 0;
        int minCount = 100;
        for (int i = 0;i < list.size(); i++) {
            int vovelCount = 0;
            for (int j = 0;j < list[i].count(); j++) {
                if(list[i][j] == 'a' || list[i][j] == 'e' || list[i][j] == 'i' || list[i][j] == 'u' || list[i][j] == 'o'){
                    vovelCount++;
                }
            }
            if(vovelCount < minCount){
                minCount = vovelCount;
                minIdx = i;
            }
        }
        ui->lineEdit_word->setText(list[minIdx]);
        ui->lineEdit_word_idx->setText(QString::number(minIdx+1));
        QString reverseWord;
        std::string str;
        std::string minstr = list[minIdx].toStdString();
        str.resize(minstr.size());
        int i = 0;
        for(int j = minstr.size()-1;j >= 0; j--){
            str[i++] = minstr[j];
        }
        reverseWord = QString::fromStdString(str);

        QString reverseWordSpaces = " " + reverseWord + " ";
        std::string strreverseWordSpaces = reverseWordSpaces.toStdString();
        QString line_2 = " " + ui->textEdit_text_2->toPlainText() + " ";
        QString lowerline_2 = line_2.toLower();
        std::string strlowerline_2 = RemoveSpaces(lowerline_2.toStdString());

        int count = 0;
        int Idx = 0;

        for(int i = 0; i < strlowerline_2.size(); i++){
            for (int j = 0; j < strreverseWordSpaces.size() && i < strlowerline_2.size() ; j++) {
                if(strlowerline_2[i] == ' '){
                    Idx++;
                }
                if(strreverseWordSpaces[j] == strlowerline_2[i]){
                    count++;
                }else{
                    j--;
                    count = 0;
                }
                if(count == strreverseWordSpaces.size()){
                    break;
                }
                i++;
            }
        }

        ui->lineEdit_rword->setText(reverseWord);
        ui->lineEdit_rword_idx->setText(QString::number(Idx));
    }else if(btn->text() == "Clear"){
        ui->textEdit->clear();
        ui->textEdit_text_2->clear();
        ui->lineEdit_rword->clear();
        ui->lineEdit_rword_idx->clear();
        ui->lineEdit_word->clear();
        ui->lineEdit_word_idx->clear();
    }
}

