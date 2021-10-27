#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "subscription.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionEdit_table_triggered();

    void on_actionBack_to_table_triggered();

    void resizeEvent(QResizeEvent*);

private:
    Ui::MainWindow *ui;
    std::vector<Subscription> SubscriptionVector;
};
#endif // MAINWINDOW_H
