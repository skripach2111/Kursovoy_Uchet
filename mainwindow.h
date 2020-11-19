#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemodule.h"
#include "addorsetstorage_dialog.h"
#include "addorsetuser_dialog.h"

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

    void updateComingInvoicesTable();
    void updateSenderInvoicesTable();
    void updateMovingInvoicesTable();
    void updateStornedInvoicesTable();
    void updateStorageTable();
    void updateUserTable();

private slots:
    void slot_pushButton_MainInvoices_clicked();
    void slot_pushButton_MainProducts_clicked();
    void slot_pushButton_MainStorages_clicked();
    void slot_pushButton_MainReports_clicked();
    void slot_pushButton_MainProviders_clicked();
    void slot_pushButton_MainClients_clicked();
    void slot_pushButton_MainUsers_clicked();
    void slot_pushButton_AddStorage_clicked();
    void slot_pushButton_AddUser_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
