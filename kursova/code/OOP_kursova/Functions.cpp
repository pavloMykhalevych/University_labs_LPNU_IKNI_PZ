#include "Functions.h"
#include <algorithm>
#include <map>
#include <string>

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

void ShowSameType(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect, const enum SubscriptionType type){
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

void ShowSameDuration(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect){
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

void ShowMostType(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect){
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
