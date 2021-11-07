#include "Functions.h"
#include <algorithm>
#include <map>
#include <string>
#include <QMessageBox>

// Removes unnecessary spaces.
void RemoveSpaces(std::string& myString){
    for (size_t i = 1; i <= myString.size(); ++i) {
        if(i-1 == 0 && myString[i - 1] == ' '){
            myString.erase(myString.begin() + (i - 1));
            myString.shrink_to_fit();
            i--;
            continue;
        }
        if (myString[i - 1] == ' ' && (myString[i] == ' ' || myString[i] == '\0')) {
            myString.erase(myString.begin() + (i - 1));
            myString.shrink_to_fit();
            i--;
        }
    }
}

// Show person with the subscription type you pick.
void ShowSameType(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect, const enum SubscriptionType type){
    if(mySubscriptionVect.empty()){
        QMessageBox::information(NULL,"Info","There is no data.");
        return;
    }
    for (auto i = 0; i < tableWidget->rowCount(); i++) {
        for (auto j = 0; j < tableWidget->columnCount(); j++) {
            tableWidget->item(i,j)->setText("");
        }
    }
    int count = 0;
    for(const auto& subscription : mySubscriptionVect){
        if(subscription.GetSubscriptionType() == type){
            tableWidget << subscription;
            ++count;
        }
    }
    if(count == 0){
        QMessageBox::information(NULL,"Info","There is no person with such subscription.");
    }
}

// Show people who have the most used duration.
void ShowSameDuration(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect){
    if(mySubscriptionVect.empty()){
        QMessageBox::information(NULL,"Info","There is no data.");
        return;
    }
    std::map<std::string,int> myMap;
    for(const auto& subscription : mySubscriptionVect){
        myMap[subscription.GetDuration()]++;
    }
    std::map<std::string,int>::iterator maxIter =
            std::max_element(myMap.begin(),myMap.end(),[](const std::pair<std::string,int>& a, const std::pair<std::string,int>& b)->bool
            {
                return a.second < b.second;
            });
    for (auto i = 0; i < tableWidget->rowCount(); i++) {
        for (auto j = 0; j < tableWidget->columnCount(); j++) {
            tableWidget->item(i,j)->setText("");
        }
    }
    for(const auto& subscription : mySubscriptionVect){
        if(subscription.GetDuration() == maxIter->first){
            tableWidget << subscription;
        }
    }
}

// Show people who have the most used subscription type.
void ShowMostType(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect){
    if(mySubscriptionVect.empty()){
        QMessageBox::information(NULL,"Info","There is no data.");
        return;
    }
    int count_1 = 0;
    int count_2 = 0;
    int count_3 = 0;
    int count_4 = 0;
    for(const auto& subscription : mySubscriptionVect){
        switch(subscription.GetSubscriptionType()){
        case SubscriptionType::SimpleFirstHalfDay:{
            ++count_1;
            break;
        }
        case SubscriptionType::SimpleFullDay:{
            ++count_2;
            break;
        }
        case SubscriptionType::LuxFullDay:{
            ++count_3;
            break;
        }
        case SubscriptionType::SuperLuxFullDay:{
            ++count_4;
            break;
        }
        }
    }

    const auto maxValue = std::max({count_1,count_2,count_3,count_4});

    SubscriptionType type;

    if(maxValue == count_1){
        type = SubscriptionType::SimpleFirstHalfDay;
    }else if(maxValue == count_2){
        type = SubscriptionType::SimpleFullDay;
    }else if(maxValue == count_3){
        type = SubscriptionType::LuxFullDay;
    }else if(maxValue == count_4){
        type = SubscriptionType::SuperLuxFullDay;
    }
    for (auto i = 0; i < tableWidget->rowCount(); i++) {
        for (auto j = 0; j < tableWidget->columnCount(); j++) {
            tableWidget->item(i,j)->setText("");
        }
    }
    for(const auto& subscription : mySubscriptionVect){
        if(subscription.GetSubscriptionType() == type){
            tableWidget << subscription;
        }
    }
}

// Function for avoiding duplication.
void FuncForResizeEvent(QTableWidget* tableWidget, MainWindow * mainWindow){
    int widthToSet = (mainWindow->width() - 340) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    tableWidget->setColumnWidth(1,widthToSet);
    tableWidget->setColumnWidth(2,widthToSet);
    tableWidget->setColumnWidth(4,widthToSet);
}

// Function for avoiding duplication.
void SetTableWidget(QTableWidget* tableWidget, MainWindow * mainWindow){
    tableWidget->setColumnWidth(0,50);
    int widthToSet = (mainWindow->width() - 340) / 3;
    if(widthToSet < 150){
        widthToSet = 150;
    }
    tableWidget->setColumnWidth(1,widthToSet);
    tableWidget->setColumnWidth(2,widthToSet);
    tableWidget->setColumnWidth(3,150);
    tableWidget->setColumnWidth(4,widthToSet);
    tableWidget->setColumnWidth(5,140-3);

    for (auto i = 0; i < tableWidget->rowCount(); i++) {
        for (auto j = 0; j < tableWidget->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(i,j,item);
        }
    }
}
