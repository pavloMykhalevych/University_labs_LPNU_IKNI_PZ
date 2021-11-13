#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <QMessageBox>
#include <map>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
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

int FindIndex(const QString line, int position){
    int count = 0;
    for(int i = position; i >= 0; --i){
        if(line[i] == ' '){
            count++;
        }
    }
    return count;
}

void MainWindow::MySlot()
{
    QPushButton* btn = (QPushButton *) sender();
    if(btn->text() == "Start"){
        QStringList lineList = ui->textEdit_text->toPlainText().toLower().split('.',Qt::SkipEmptyParts);
        for (int i = 1; i < lineList.size() ; ++i) {
            lineList[i].remove('\n');
        }
        //Task
        if(ui->spinBox_line_idx->value() > lineList.size() || lineList.size() == 1){
            QMessageBox::warning(nullptr,"Incorrect line index!","Text has only "
                + QString::number(lineList.size()) + " lines!\nPlease, change the line index.");
            return;
        }
        QString tmp = lineList[lineList.size()-2];
        lineList[lineList.size()-2] = lineList[ui->spinBox_line_idx->value()-1];
        lineList[ui->spinBox_line_idx->value()-1] = tmp;

        for(int i = 0; i < lineList.size(); ++i){
            ui->textEdit_change_text->append(lineList[i]);
        }

        //Search
        if(ui->lineEdit_word->text() == ""){
            QMessageBox::warning(nullptr,"Incorrect input!","Please, enter the word to find.");
            return;
        }
        QString word = QString::fromStdString(RemoveSpaces((" " + ui->lineEdit_word->text()).toLower().toStdString())) + " ";
        for(auto&& line : lineList){
            line = QString::fromStdString(RemoveSpaces((" " + line).toStdString())) + " ";
        }

        std::map<QChar,int> map;
        map[word[word.size() - 1]] = word.size();
        for (int i = 0; i < word.size() - 1 ; i++) {
            map[word[i]] = word.size()-1-i;
        }

        for(int m = 0; m < lineList.size(); ++m){
            const auto line = lineList[m];
            bool l_flag = false;
            for (int i = word.size()-1; i < line.size();) {
                int iCur = i;
                bool flag = false;
                for(int j = word.size()-1; j >= 0;){
                    if(line[i] == word[j]){
                        if(j == 0){
                            flag = true;
                            break;
                        }
                        --j;
                        --i;
                    }else{
                        auto it = map.find(line[i]);
                        if(it == map.end()){
                            i = iCur + j;
                            break;
                        }
                        if(it->second < i){
                            i = iCur + it->second;
                        }else{
                            i = iCur + 1;
                        }
                        break;
                    }
                }
                if(flag){
                    ui->textEdit_result->append("Found in line " + QString::number(m + 1) + " : " + QString::number(FindIndex(line, i)) + " word.");
                    i = i + word.size();
                    l_flag = true;
                }
            }
            if(!l_flag){
                ui->textEdit_result->append("Word not found in line " + QString::number(m + 1) + ".");
            }
        }


    }else if(btn->text() == "Clear"){
        ui->textEdit_change_text->clear();
        ui->textEdit_result->clear();
        ui->textEdit_text->clear();
        ui->lineEdit_word->clear();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

