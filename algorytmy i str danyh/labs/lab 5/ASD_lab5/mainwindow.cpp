#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(MySlot()));
    connect(ui->pushButton_init,SIGNAL(clicked()),this,SLOT(MySlot()));
}




int partition (std::string *arr, int low, int high,QTextEdit* textEdit, int count)
{
    std::string pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j] < pivot)
        {
            i++;
            std::string t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
        }
    }

    std::string t = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = t;
    textEdit->append("");
    textEdit->append("Pivot = " + QString::fromStdString(arr[i+1]));
    std::string res = "";
    for (int i = 0;i < count; i++) {
        res += arr[i];
        if(i < count-1){
            res += ", ";
        }
    }
    textEdit->append(QString::fromStdString(res));

    return (i + 1);
}


void quickSort(std::string * arr, int low, int high,QTextEdit* textEdit, int count)
{
    if (low < high)
    {

        int pi = partition(arr, low, high,textEdit, count);


        quickSort(arr, low, pi - 1,textEdit, count);
        quickSort(arr, pi + 1, high,textEdit, count);
    }
}


void MainWindow::MySlot(){
    QPushButton* btn = (QPushButton*)sender();
    if(btn->text()=="Clear"){
        ui->textEdit_enter->clear();
        ui->textEdit_result->clear();
        ui->textEdit_steps->clear();
    }else if(btn->text()=="Random init"){
        ui->textEdit_enter->clear();
        ui->textEdit_result->clear();
        ui->textEdit_steps->clear();
        std::vector<QString> city = {"Lviv","Kharkow","Vrotslav","Dnipro","Singapur","Istanbul","Shanghay","Paris","Mykolaiv","Madrid","London","Vadodara",
                          "Monrovia","Sydney","Zanzibar","Uzhorod","Seoul","Dortmund","Barselona","Osaka","Damaskus","Rome","Campinas","Tokyo",
                         "Belgrade","Mumbai","Mariupol","Dhaka","Sorocaba","Karachi","Kolkata","Santiago","Budapest","Lagos","Lahore","Tangshan",
                         "Varshava","Jakarta","Bradford","Chicago","Kyiv","Katowice","Kawasaki","Lima","Semarang","Tehran","Wuhan","Kingston",
                         "Pune","Hannover","Dallas","Florence","Miami","Tashkent","Florida","Hamilton","Atlanta","Contagem","Dalian","Jinan"};
        srand(time(NULL));
        QString data = "";
        int count = rand() % 15 + 7;
        for (int i = 0; i < count ; i++) {
            int index;
            while(1){
                index = rand() % city.size();
                if(city[index] != "0"){
                    break;
                }
            }
            data += city[index];
            city[index] = "0";
            if(i != count - 1){
                data += ", ";
            }
        }
        ui->textEdit_enter->append(data);
    }else if(btn->text()=="Start"){
        ui->textEdit_result->clear();
        ui->textEdit_steps->clear();
        std::vector<QString> city;
        QString enter_data = ui->textEdit_enter->toPlainText();
        QStringList enter_cities = enter_data.split(',');
        enter_data.clear();
        for (int i = 0;i < enter_cities.length(); i++) {
            enter_data += enter_cities[i];
        }
        enter_cities.clear();
        enter_cities = enter_data.split(" ");
        for (int i = 0;i < enter_cities.length(); i++) {
            if(enter_cities[i].length() == 8){
                city.push_back(enter_cities[i]);
            }
        }

        //quicksort

        std::string city_arr[city.size()];
        for (std::size_t i = 0;i < city.size(); i++) {
            city_arr[i] = city[i].toStdString();
        }

        quickSort(city_arr,0,city.size()-1,ui->textEdit_steps,city.size());


        std::string res = "";
        for (std::size_t i = 0;i < city.size(); i++) {
            res += city_arr[i];
            if(i < city.size()-1){
                res += ", ";
            }
        }
        ui->textEdit_result->append(QString::fromStdString(res));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

