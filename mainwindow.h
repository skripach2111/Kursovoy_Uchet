#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemodule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    DatabaseModule db;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setConnection(QSqlDatabase db_connection, QString login, QString password);
    void setWorkspaceForHeadOfStorage();
    void setWorkspaceForAccountant();

    void updateComingInvoices();
    void updateSenderInvoices();
    void updateMovingInvoices();
    void updateStornedInvoices();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
