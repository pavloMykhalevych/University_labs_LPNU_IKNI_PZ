#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include <QTableWidget>

#include "subscription.h"
#include "mainwindow.h"

void RemoveSpaces(std::string& myString);

void ShowSameType(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect,const enum SubscriptionType type);

void ShowSameDuration(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect);

void ShowMostType(QTableWidget* tableWidget,const std::vector<Subscription>& mySubscriptionVect);

void FuncForResizeEvent(QTableWidget* tableWidget, MainWindow * mainWindow);

void SetTableWidget(QTableWidget* tableWidget, MainWindow * mainWindow);

#endif // FUNCTIONS_H
