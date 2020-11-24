#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemodule.h"
#include "addorsetstorage_dialog.h"
#include "addorsetuser_dialog.h"
#include "addorsetclient_dialog.h"
#include "addorsetprovider_dialog.h"
#include "addorsetproduct_dialog.h"
#include "addinvoice_dialog.h"
#include "moreaboutinvoice_dialog.h"
#include "printpreview_dialog.h"

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
    void updateClientTable();
    void updateProviderTable();
    void updateProductTable();

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
    void slot_pushButton_AddClient_clicked();
    void slot_pushButton_AddProvider_clicked();
    void slot_pushButton_AddProduct_clicked();
    void slot_pushButton_AddInvoice_clicked();
    void slot_pushButton_tabWidget_Invoices_currentChanget(int number);

    void slot_pushButton_SetStorage_clicked();
    void slot_pushButton_SetUser_clicked();
    void slot_pushButton_SetClient_clicked();
    void slot_pushButton_SetProvider_clicked();
    void slot_pushButton_SetProduct_clicked();

    void slot_pushButton_RemoveStorage_clicked();
    void slot_pushButton_RemoveUser_clicked();
    void slot_pushButton_RemoveClient_clicked();
    void slot_pushButton_RemoveProvider_clicked();
    void slot_pushButton_RemoveProduct_clicked();

    void slot_pushButton_ToFormedReportDeliveryReport_clicked();
    void slot_pushButton_ReportBySalesForm_clicked();

    void on_pushButton_PopularityTableForm_clicked();

    void on_pushButton_FinancialReportForm_clicked();

    void on_pushButton_StornInvoice_clicked();

    void on_pushButton_MoreAboutInvoice_clicked();

    void on_pushButton_PrintDeliveryReport_clicked();

    void on_pushButton_PrintSaleReport_clicked();

    void on_pushButton_PopularityTablePrint_clicked();

    void on_pushButton_FinancialReportPrint_clicked();

    void on_pushButton_ToFormedReportDeliveryReport_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
