#include "subscription.h"
#include "fstream"
#include "iostream"
#include "iomanip"

Subscription::Subscription()
{
    this->SetDuration("");
    this->SetNumber(std::numeric_limits<uint64_t>::max());
    this->SetPersonInfo("", "", "");
    this->SetSubscriptionType(SubscriptionType::SimpleFirstHalfDay);
}

Subscription::Subscription(std::string surname, std::string name, std::string phoneNumber,
                           SubscriptionType type, std::string duration, uint64_t number)
{
    this->SetDuration(duration);
    this->SetNumber(number);
    this->SetPersonInfo(surname, name, phoneNumber);
    this->SetSubscriptionType(type);
}

Subscription::Subscription(Subscription &otherSubscription)
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

void Subscription::SetPersonInfo(std::string surname, std::string name, std::string phoneNumber)
{
    this->m_person.m_surname = surname;
    this->m_person.m_name = name;
    this->m_person.m_phoneNumber = phoneNumber;
}

uint64_t Subscription::GetNumber() const
{
    return this->m_number;
}

void Subscription::SetNumber(uint64_t newNumber)
{
    this->m_number = newNumber;
}

std::string Subscription::GetDuration() const
{
    return this->m_duration;
}

void Subscription::SetDuration(std::string newDuration)
{
    this->m_duration = newDuration;
}

SubscriptionType Subscription::GetSubscriptionType() const
{
    return this->m_subscriptionType;
}

void Subscription::SetSubscriptionType(SubscriptionType newSubscriptionType)
{
    this->m_subscriptionType = newSubscriptionType;
}

Subscription::~Subscription()
{

}

void operator>>(std::string filePath,Subscription& mySubscription){

}

void operator<<(std::string filePath,const Subscription& mySubscription){
    std::ofstream file;
    file.open(filePath);
    std::string myType;
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
