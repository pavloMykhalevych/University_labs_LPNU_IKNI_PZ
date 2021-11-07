#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <vector>

#include <QTableWidget>

#include "Person.h"
#include "SubscriptionType.h"

class Subscription
{
public:
    friend void operator>>(std::string filePath,std::vector<Subscription>& mySubscription);
    friend void operator<<(std::string filePath,const std::vector<Subscription>& mySubscription);
    friend void operator>>(QTableWidget* tableWidget,std::vector<Subscription>& mySubscription);
    friend void operator<<(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscription);
    friend void operator<<(QTableWidget* tableWidget,const Subscription& mySubscription);

    Subscription();
    Subscription(const Person& person, const SubscriptionType& type, const std::string& duration, const uint64_t& number);
    Subscription(const std::string& surname, const std::string& name, const std::string& phoneNumber,
                 const SubscriptionType& type, const std::string& duration, const uint64_t& number);
    Subscription(const Subscription& otherSubscription);

    Person GetPersonInfo() const;
    void SetPersonInfo(const Person& person);

    std::string GetSurname() const;
    std::string GetName() const;
    std::string GetPhoneNumber() const;
    void SetPersonInfo(const std::string& surname, const std::string& name, const std::string& phoneNumber);

    uint64_t GetNumber() const;
    void SetNumber(const uint64_t& newNumber);

    std::string GetDuration() const;
    void SetDuration(const std::string& newDuration);

    SubscriptionType GetSubscriptionType() const;
    void SetSubscriptionType(const SubscriptionType& newSubscriptionType);

    ~Subscription();

private:
    Person m_person;
    SubscriptionType m_subscriptionType;
    std::string m_duration;
    uint64_t m_number;
};



#endif // SUBSCRIPTION_H
