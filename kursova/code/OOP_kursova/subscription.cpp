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
    int count = 0;
    while(std::getline(strstream, token, '|')){
        RemoveSpaces(token);
        tokenVect.push_back(token);
        ++count;
    }
    if(count != 6){
        throw std::runtime_error("The input data isn't correct!");
        return;
    }
    if(!tokenVect.empty()){
        if(tokenVect[5].size() > 22 || tokenVect[5].size() < 6){
            throw std::runtime_error("The duration is incorrect!");
            return;
        }
        mySubscription.SetDuration(tokenVect[5]);
        if(tokenVect[0].empty()){
            throw std::runtime_error("There is no number!");
            return;
        }
        mySubscription.SetNumber(std::stoi(tokenVect[0]));
        if(tokenVect[1].size() > 50 || tokenVect[5].size() < 3){
            throw std::runtime_error("The surname is incorrect!");
            return;
        }
        person.m_surname = tokenVect[1];
        if(tokenVect[2].size() > 50 || tokenVect[5].size() < 3){
            throw std::runtime_error("The name is incorrect!");
            return;
        }
        person.m_name = tokenVect[2];
        if(tokenVect[3].size() > 30 || tokenVect[5].size() < 10){
            throw std::runtime_error("The phone number is incorrect!");
            return;
        }
        person.m_phoneNumber = tokenVect[3];
        mySubscription.SetPersonInfo(person);
        if(tokenVect[4].empty()){
            throw std::runtime_error("There is no subscription type!");
            return;
        }
        subscriptionType = tokenVect[4];
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

    std::vector<std::string> tokenVect{6};
    for(auto i = 0; i < 6; ++i){
        tokenVect[i] = tableWidget->item(0,i)->text().toStdString();
    }
    if(tokenVect[5].size() > 22 || tokenVect[5].size() < 6){
        throw std::runtime_error("The duration is incorrect!");
        return;
    }
    mySubscription.SetDuration(tokenVect[5]);
    if(tokenVect[0].empty()){
        throw std::runtime_error("There is no number!");
        return;
    }
    mySubscription.SetNumber(std::stoi(tokenVect[0]));
    if(tokenVect[1].size() > 50 || tokenVect[5].size() < 3){
        throw std::runtime_error("The surname is incorrect!");
        return;
    }
    person.m_surname = tokenVect[1];
    if(tokenVect[2].size() > 50 || tokenVect[5].size() < 3){
        throw std::runtime_error("The name is incorrect!");
        return;
    }
    person.m_name = tokenVect[2];
    if(tokenVect[3].size() > 30 || tokenVect[5].size() < 10){
        throw std::runtime_error("The phone number is incorrect!");
        return;
    }
    person.m_phoneNumber = tokenVect[3];
    mySubscription.SetPersonInfo(person);
    if(tokenVect[4].empty()){
        throw std::runtime_error("There is no subscription type!");
        return;
    }
    subscriptionType = tokenVect[4];
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
    mySubscriptionVect.push_back(mySubscription);
}

void operator<<(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect){

}
