#include <subscription.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <QString>
#include <QStringList>

Subscription::Subscription()
{
    this->SetDuration("");
    this->SetNumber(std::numeric_limits<uint64_t>::max());
    this->SetPersonInfo("", "", "");
    this->SetSubscriptionType(SubscriptionType::SimpleFirstHalfDay);
}

Subscription::Subscription(const Person& person, const SubscriptionType& type, const std::string& duration, const uint64_t& number)
{
    this->SetDuration(duration);
    this->SetNumber(number);
    this->SetPersonInfo(person);
    this->SetSubscriptionType(type);
}

Subscription::Subscription(const std::string& surname, const std::string& name, const std::string& phoneNumber,
                           const SubscriptionType& type, const std::string& duration, const uint64_t& number)
{
    this->SetDuration(duration);
    this->SetNumber(number);
    this->SetPersonInfo(surname, name, phoneNumber);
    this->SetSubscriptionType(type);
}

Subscription::Subscription(const Subscription& otherSubscription)
{
    this->SetDuration(otherSubscription.m_duration);
    this->SetNumber(otherSubscription.m_number);
    this->SetPersonInfo(otherSubscription.m_person.m_surname,
                        otherSubscription.m_person.m_name,
                        otherSubscription.m_person.m_phoneNumber);
    this->SetSubscriptionType(otherSubscription.m_subscriptionType);
}

Person Subscription::GetPersonInfo() const
{
    return this->m_person;
}

void Subscription::SetPersonInfo(const std::string& surname, const std::string& name, const std::string& phoneNumber)
{
    this->m_person.m_surname = surname;
    this->m_person.m_name = name;
    this->m_person.m_phoneNumber = phoneNumber;
}

void Subscription::SetPersonInfo(const Person &person)
{
    this->m_person.m_surname = person.m_surname;
    this->m_person.m_name = person.m_name;
    this->m_person.m_phoneNumber = person.m_phoneNumber;
}

std::string Subscription::GetSurname() const
{
    return m_person.m_surname;
}

std::string Subscription::GetName() const
{
    return m_person.m_name;
}

std::string Subscription::GetPhoneNumber() const
{
    return m_person.m_phoneNumber;
}

uint64_t Subscription::GetNumber() const
{
    return this->m_number;
}

void Subscription::SetNumber(const uint64_t& newNumber)
{
    this->m_number = newNumber;
}

std::string Subscription::GetDuration() const
{
    return this->m_duration;
}

void Subscription::SetDuration(const std::string& newDuration)
{
    this->m_duration = newDuration;
}

SubscriptionType Subscription::GetSubscriptionType() const
{
    return this->m_subscriptionType;
}

void Subscription::SetSubscriptionType(const SubscriptionType& newSubscriptionType)
{
    this->m_subscriptionType = newSubscriptionType;
}

Subscription::~Subscription()
{

}

void operator>>(std::string filePath,std::vector<Subscription>& mySubscriptionVect){
    Subscription mySubscription;
    Person person;
    std::string subscriptionType;

    std::ifstream file;
    file.open(filePath);
    std::string line;
    std::getline(file, line);
    std::stringstream strstream(line);
    std::vector<std::string> tokenVect;
    std::string token;
    while(std::getline(strstream, token, '|')){
        RemoveSpaces(token);
        tokenVect.push_back(token);
    }
    if(tokenVect.size() != 5){
        throw std::runtime_error("The input data isn't correct!");
        return;
    }
    if(!tokenVect.empty()){
        if(tokenVect[4].size() > 22 || tokenVect[4].size() < 6){
            throw std::runtime_error("The duration is incorrect!");
            return;
        }
        mySubscription.SetDuration(tokenVect[4]);
        if(tokenVect[0].size() > 50 || tokenVect[0].size() < 3){
            throw std::runtime_error("The surname is incorrect!");
            return;
        }
        person.m_surname = tokenVect[0];
        if(tokenVect[1].size() > 50 || tokenVect[1].size() < 3){
            throw std::runtime_error("The name is incorrect!");
            return;
        }
        person.m_name = tokenVect[1];
        if(tokenVect[2].size() > 30 || tokenVect[2].size() < 10){
            throw std::runtime_error("The phone number is incorrect!");
            return;
        }
        person.m_phoneNumber = tokenVect[2];
        mySubscription.SetPersonInfo(person);
        if(tokenVect[3].empty()){
            throw std::runtime_error("There is no subscription type!");
            return;
        }
        subscriptionType = tokenVect[3];
        if(subscriptionType.find("Lux type full day") != std::string::npos){
            mySubscription.SetSubscriptionType(SubscriptionType::LuxFullDay);
        }else if(subscriptionType.find("Simple type first half day") != std::string::npos){
            mySubscription.SetSubscriptionType(SubscriptionType::SimpleFirstHalfDay);
        }else if(subscriptionType.find("Simple type full day") != std::string::npos){
            mySubscription.SetSubscriptionType(SubscriptionType::SimpleFullDay);
        }else if(subscriptionType.find("Super Lux type full day") != std::string::npos){
            mySubscription.SetSubscriptionType(SubscriptionType::SuperLuxFullDay);
        }else{
            throw std::runtime_error("There isn't such a subscription type!");
            return;
        }
    }else{
        throw std::runtime_error("The input file is empty!");
        return;
    }
    if(!mySubscriptionVect.empty()){
        mySubscription.SetNumber(mySubscriptionVect.back().GetNumber() + 1);
    }else{
        mySubscription.SetNumber(1);
    }
    mySubscriptionVect.push_back(mySubscription);
    /*QString text_line = QString::fromStdString(line);
    if(!text_line.isEmpty()){
        QStringList valuestr = text_line.split('|');
        mySubscription.SetDuration(valuestr[5].toStdString());
        mySubscription.SetNumber(valuestr[0].toInt());
        person.m_surname = valuestr[1].toStdString();
        person.m_name = valuestr[2].toStdString();
        person.m_phoneNumber = valuestr[3].toStdString();
        mySubscription.SetPersonInfo(person);
        subscriptionType = valuestr[4].toStdString();
    }else{

    } */
}

void operator<<(std::string filePath,const std::vector<Subscription>& mySubscriptionVect){
    std::ofstream file;
    file.open(filePath);
    std::string myType;
    for(const auto& mySubscription : mySubscriptionVect){
    switch(mySubscription.m_subscriptionType){
    case SubscriptionType::LuxFullDay:{
        myType = "Lux type full day";
        break;
    }
    case SubscriptionType::SimpleFirstHalfDay:{
        myType = "Simple type first half day";
        break;
    }
    case SubscriptionType::SimpleFullDay:{
        myType = "Simple type full day";
        break;
    }
    case SubscriptionType::SuperLuxFullDay:{
        myType = "Super Lux type full day";
        break;
    }
    }

    file << std::setw(10) << std::left << mySubscription.m_number << std::setw(1) << "|"
         << std::setw(50) << mySubscription.m_person.m_surname << std::setw(1) << "|"
         << std::setw(50) << mySubscription.m_person.m_name << std::setw(1) << "|"
         << std::setw(20) << mySubscription.m_person.m_phoneNumber << std::setw(1) << "|"
         << std::setw(40) << myType<< std::setw(1) << "|"
         << std::setw(20) << mySubscription.m_duration << std::setw(1) << "|" << std::endl;
    }
}

void operator>>(QTableWidget* tableWidget,std::vector<Subscription>& mySubscriptionVect){
    Subscription mySubscription;
    Person person;
    std::string subscriptionType;

    std::vector<std::string> tokenVect{5};
    for(auto i = 0; i < 5; ++i){
        tokenVect[i] = tableWidget->item(0,i)->text().toStdString();
    }
    if(tokenVect[4].size() > 22 || tokenVect[4].size() < 6){
        throw std::runtime_error("The duration is incorrect!");
        return;
    }
    mySubscription.SetDuration(tokenVect[4]);
    if(tokenVect[0].size() > 50 || tokenVect[0].size() < 3){
        throw std::runtime_error("The surname is incorrect!");
        return;
    }
    person.m_surname = tokenVect[0];
    if(tokenVect[1].size() > 50 || tokenVect[1].size() < 3){
        throw std::runtime_error("The name is incorrect!");
        return;
    }
    person.m_name = tokenVect[1];
    if(tokenVect[2].size() > 30 || tokenVect[2].size() < 10){
        throw std::runtime_error("The phone number is incorrect!");
        return;
    }
    person.m_phoneNumber = tokenVect[2];
    mySubscription.SetPersonInfo(person);
    if(tokenVect[3].empty()){
        throw std::runtime_error("There is no subscription type!");
        return;
    }
    subscriptionType = tokenVect[3];
    if(subscriptionType.find("Lux type full day") != std::string::npos){
        mySubscription.SetSubscriptionType(SubscriptionType::LuxFullDay);
    }else if(subscriptionType.find("Simple type first half day") != std::string::npos){
        mySubscription.SetSubscriptionType(SubscriptionType::SimpleFirstHalfDay);
    }else if(subscriptionType.find("Simple type full day") != std::string::npos){
        mySubscription.SetSubscriptionType(SubscriptionType::SimpleFullDay);
    }else if(subscriptionType.find("Super Lux type full day") != std::string::npos){
        mySubscription.SetSubscriptionType(SubscriptionType::SuperLuxFullDay);
    }else{
        throw std::runtime_error("There isn't such a subscription type!");
        return;
    }
    if(!mySubscriptionVect.empty()){
        mySubscription.SetNumber(mySubscriptionVect.back().GetNumber() + 1);
    }else{
        mySubscription.SetNumber(1);
    }
    mySubscriptionVect.push_back(mySubscription);
}

void operator<<(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect){
    std::string myType;
    tableWidget->setRowCount(mySubscriptionVect.size());
    for (auto i = 0; i < tableWidget->rowCount(); i++) {
        for (auto j = 0; j < tableWidget->columnCount(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("");
            item->setTextAlignment(Qt::AlignCenter);
            tableWidget->setItem(i,j,item);
        }
    }
    for(size_t i = 0; i < mySubscriptionVect.size(); ++i){
        switch(mySubscriptionVect[i].GetSubscriptionType()){
        case SubscriptionType::LuxFullDay:{
            myType = "Lux type full day";
            break;
        }
        case SubscriptionType::SimpleFirstHalfDay:{
            myType = "Simple type first half day";
            break;
        }
        case SubscriptionType::SimpleFullDay:{
            myType = "Simple type full day";
            break;
        }
        case SubscriptionType::SuperLuxFullDay:{
            myType = "Super Lux type full day";
            break;
        }
        }
        tableWidget->item(i,0)->setText(QString::number(mySubscriptionVect[i].GetNumber()));
        tableWidget->item(i,1)->setText(QString::fromStdString(mySubscriptionVect[i].GetSurname()));
        tableWidget->item(i,2)->setText(QString::fromStdString(mySubscriptionVect[i].GetName()));
        tableWidget->item(i,3)->setText(QString::fromStdString(mySubscriptionVect[i].GetPhoneNumber()));
        tableWidget->item(i,4)->setText(QString::fromStdString(myType));
        tableWidget->item(i,5)->setText(QString::fromStdString(mySubscriptionVect[i].GetPhoneNumber()));
        }
}

void operator<<(QTableWidget* tableWidget,const Subscription& mySubscription){
    std::string myType;
    tableWidget->insertRow( tableWidget->rowCount() );
    for (auto j = 0; j < tableWidget->columnCount(); j++) {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText("");
        item->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(tableWidget->rowCount()-1,j,item);
    }
    switch(mySubscription.GetSubscriptionType()){
    case SubscriptionType::LuxFullDay:{
        myType = "Lux type full day";
        break;
    }
    case SubscriptionType::SimpleFirstHalfDay:{
        myType = "Simple type first half day";
        break;
    }
    case SubscriptionType::SimpleFullDay:{
        myType = "Simple type full day";
        break;
    }
    case SubscriptionType::SuperLuxFullDay:{
        myType = "Super Lux type full day";
        break;
    }
    }
    tableWidget->item(tableWidget->rowCount()-1,0)->setText(QString::number(mySubscription.GetNumber()));
    tableWidget->item(tableWidget->rowCount()-1,1)->setText(QString::fromStdString(mySubscription.GetSurname()));
    tableWidget->item(tableWidget->rowCount()-1,2)->setText(QString::fromStdString(mySubscription.GetName()));
    tableWidget->item(tableWidget->rowCount()-1,3)->setText(QString::fromStdString(mySubscription.GetPhoneNumber()));
    tableWidget->item(tableWidget->rowCount()-1,4)->setText(QString::fromStdString(myType));
    tableWidget->item(tableWidget->rowCount()-1,5)->setText(QString::fromStdString(mySubscription.GetPhoneNumber()));

}
