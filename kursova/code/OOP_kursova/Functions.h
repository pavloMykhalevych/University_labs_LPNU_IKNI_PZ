#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include <QTableWidget>

#include "subscription.h"

void RemoveSpaces(std::string& myString);

void ShowSameType(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect,const enum SubscriptionType type);

void ShowSameDuration(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect);

void ShowMostType(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect);

#endif // FUNCTIONS_H
