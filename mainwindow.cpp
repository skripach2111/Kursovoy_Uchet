#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWorkspaceForHeadOfStorage()
{
    ui->pushButton_MainUsers->setVisible(false);
    ui->pushButton_MainProviders->setVisible(false);
    ui->pushButton_MainClients->setVisible(false);
    ui->pushButton_MainProducts->setVisible(false);
    ui->pushButton_MainStorages->setVisible(false);
}

void MainWindow::setWorkspaceForAccountant()
{
    ui->pushButton_MainStorages->setVisible(false);
    ui->pushButton_MainUsers->setVisible(false);
    ui->pushButton_AddInvoice->setVisible(false);
    ui->pushButton_StornInvoice->setVisible(false);
}

void MainWindow::updateComingInvoices()
{
    QList <invoice> listInvoices;
    listInvoices = db.getListInvoiceByTypeAvialableConnectedUser(1);
    ui->tableWidget_comingInvoices->setRowCount(0);

    for(int i = 0; i < listInvoices.size(); i++)
    {
        ui->tableWidget_comingInvoices->insertRow(ui->tableWidget_comingInvoices->rowCount());
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 0, new QTableWidgetItem(listInvoices.at(i).id));
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 1, new QTableWidgetItem(listInvoices.at(i).provider.title));
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 2, new QTableWidgetItem(listInvoices.at(i).storageRecipient.title));
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 3, new QTableWidgetItem(listInvoices.at(i).sum));
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 4, new QTableWidgetItem(listInvoices.at(i).data.toString()));
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 5, new QTableWidgetItem(listInvoices.at(i).userRecipient.pib));
    }
}

void MainWindow::setConnection(QSqlDatabase db_connection, QString login, QString password)
{
    user tmp_user;
    tmp_user.login = login;
    tmp_user.password = password;

    db.setDatabaseConnection(db_connection, tmp_user);

    switch (db.getPrivileges())
    {
    case 3:
    {
        break;
    }
    case 5:
    {
        setWorkspaceForAccountant();
        break;
    }
    case 4:
    {
        setWorkspaceForHeadOfStorage();
        break;
    }
    case 0:
    {
        ui->pushButton_MainInvoices->setText("Верну 0");
    }
    }

    updateComingInvoices();
}
