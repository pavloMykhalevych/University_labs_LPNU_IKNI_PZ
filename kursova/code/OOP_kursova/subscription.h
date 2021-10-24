#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H
#include <vector>
#include "Person.h"
#include "SubscriptionType.h"

class Subscription
{
public:
    friend void operator>>(std::string filePath,Subscription& mySubscription);
    friend void operator<<(std::string filePath,const Subscription& mySubscription);

    Subscription();
    Subscription(std::string surname, std::string name, std::string phoneNumber,
                 SubscriptionType type, std::string duration, uint64_t number);
    Subscription(Subscription& otherSubscription);

    Person GetPersonInfo() const;
    void SetPersonInfo(std::string surname, std::string name, std::string phoneNumber);

    uint64_t GetNumber() const;
    void SetNumber(uint64_t newNumber);

    std::string GetDuration() const;
    void SetDuration(std::string newDuration);

    SubscriptionType GetSubscriptionType() const;
    void SetSubscriptionType(SubscriptionType newSubscriptionType);

    ~Subscription();

private:
    Person m_person;
    SubscriptionType m_subscriptionType;
    std::string m_duration;
    uint64_t m_number;
};



#endif // SUBSCRIPTION_H
