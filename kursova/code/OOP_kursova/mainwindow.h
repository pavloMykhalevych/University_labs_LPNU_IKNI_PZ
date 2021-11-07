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

    void on_actionGive_number_Get_duration_triggered();

    void on_actionGive_surname_triggered();

    void on_actionGive_phone_number_triggered();

    void on_actionShow_most_used_type_triggered();

    void on_actionShow_with_same_duration_triggered();

    void on_pushButton_num_clicked();

    void on_pushButton_surname_clicked();

    void on_pushButton_ph_num_clicked();

    void on_actionSimple_Full_Day_triggered();

    void on_actionLux_Full_Day_triggered();

    void on_actionSuper_Lux_Full_Day_triggered();

    void on_actionSimple_First_Half_Day_triggered();

    void on_actionRead_from_file_triggered();

    void on_actionWrite_to_file_triggered();

    void on_actionAdd_triggered();

    void BackToTableOff();

private:
    Ui::MainWindow *ui;
    std::vector<Subscription> SubscriptionVector;
};
#endif // MAINWINDOW_H
