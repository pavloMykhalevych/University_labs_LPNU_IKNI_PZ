    #include "mainwindow.h"
    #include "ui_mainwindow.h"

    #include <ctime>
    #include <vector>
    #include <algorithm>
    #include <QMessageBox>

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
            std::vector<int> vect;
            std::vector<int> vectIndexes;
            std::vector<int> vectIndexes_2;
            QString text = ui->textEdit->toPlainText();
            if(!text.isEmpty()){
                QStringList valuestr = text.split(',');
                int count = valuestr.size();
                for(int j = 0; j < count; j++){
                    if(!valuestr[j].isEmpty()){
                        bool ok;
                        int value = valuestr[j].toInt(&ok);
                        if(ok){
                            vect.push_back(value);
                        }else QMessageBox::warning(NULL,"Warning!","Enter the numbers and coma!");
                    }
                }
            }else QMessageBox::warning(NULL,"Warning!","Enter the array");

            vectIndexes.resize(vect.size());

            std::iota(vectIndexes.begin(),vectIndexes.end(),0);
            std::vector InputVect = vect;

            std::sort(vect.begin(),vect.end(),[](auto a, auto b){return  (a % 10) < (b % 10);});

            for (size_t i = 0;i < vect.size(); ++i) {
                for(size_t j = 0; j < vectIndexes.size(); ++j){
                    if(vect[i] == InputVect[vectIndexes[j]]){
                        vectIndexes_2.push_back(vectIndexes[j]);
                        vectIndexes.erase(vectIndexes.begin()+j);
                        j--;
                    }
                }
            }

            size_t iter = 0;
            size_t iterComa = 0;
            QString line;
            for (const auto& a : vect) {
                line += QString::number(a);
                if(iterComa != vect.size()-1){
                    line += ", ";
                }
                iter++;
                iterComa++;
            }
            ui->textEdit_sort->append(line);

            int CompNum = 0;
            int count = 0;
            while(!vect.empty()){
                bool flag = false;
                size_t l = 0;
                size_t r = vect.size();
                size_t mid;
                while((l <= r) && (flag != true) && !vect.empty()){
                    mid = (l+r) / 2;
                    if( vect[mid] % 10 == 3){
                        ui->textEdit_result->append("Element found: index = " + QString::number(vectIndexes_2[mid]+1) + " ;");
                        flag = true;
                        vectIndexes_2.erase(vectIndexes_2.begin() + mid);
                        vect.erase(vect.begin() + mid);
                        count++;
                    }
                    if( vect[mid] % 10 > 3){
                        r = mid-1;
                    }else {
                        l = mid+1;
                    }
                    CompNum++;
                }
                if(flag == false){
                    break;
                }
            }
            if(count == 0){
                ui->textEdit_result->append("Element not found!");
            }
            ui->lineEdit->setText(QString::number(CompNum));
        }else if(btn->text()== "Clear"){
            ui->textEdit->clear();
            ui->textEdit_result->clear();
            ui->textEdit_sort->clear();
        }else if(btn->text() == "Random input"){
            std::vector<int> vect;
            ui->textEdit->clear();
            ui->textEdit_result->clear();
            ui->textEdit_sort->clear();
            vect.clear();
            srand(time(nullptr));
            for(auto i = 0; i < ui->spinBox->value(); ++i){
                vect.push_back(rand() % 500);
            }
            size_t iter = 0;
            size_t iterComa = 0;
            QString line;
            for (const auto& a : vect) {
                line += QString::number(a);
                if(iterComa != vect.size()-1){
                    line += ", ";
                }
                iter++;
                iterComa++;
            }
            ui->textEdit->append(line);
        }
    }

