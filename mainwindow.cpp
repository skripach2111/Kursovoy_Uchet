#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_MainInvoices, SIGNAL(clicked()), this, SLOT(slot_pushButton_MainInvoices_clicked()));
    connect(ui->pushButton_MainProducts, SIGNAL(clicked()), this, SLOT(slot_pushButton_MainProducts_clicked()));
    connect(ui->pushButton_MainStorages, SIGNAL(clicked()), this, SLOT(slot_pushButton_MainStorages_clicked()));
    connect(ui->pushButton_MainProviders, SIGNAL(clicked()), this, SLOT(slot_pushButton_MainProviders_clicked()));
    connect(ui->pushButton_MainReports, SIGNAL(clicked()), this, SLOT(slot_pushButton_MainReports_clicked()));
    connect(ui->pushButton_MainClients, SIGNAL(clicked()), this, SLOT(slot_pushButton_MainClients_clicked()));
    connect(ui->pushButton_MainUsers, SIGNAL(clicked()), this, SLOT(slot_pushButton_MainUsers_clicked()));

    connect(ui->pushButton_AddStorage, SIGNAL(clicked()), this, SLOT(slot_pushButton_AddStorage_clicked()));
    connect(ui->pushButton_AddUser, SIGNAL(clicked()), this, SLOT(slot_pushButton_AddUser_clicked()));
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

void MainWindow::updateComingInvoicesTable()
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

    updateComingInvoicesTable();
}

void MainWindow::slot_pushButton_MainInvoices_clicked()
{
    ui->stackedWidget_MainWorkSpace->setCurrentIndex(1);

    ui->pushButton_MainProducts->setChecked(false);
    ui->pushButton_MainProviders->setChecked(false);
    ui->pushButton_MainClients->setChecked(false);
    ui->pushButton_MainReports->setChecked(false);
    ui->pushButton_MainStorages->setChecked(false);
    ui->pushButton_MainUsers->setChecked(false);
}

void MainWindow::slot_pushButton_MainProducts_clicked()
{
    ui->stackedWidget_MainWorkSpace->setCurrentIndex(0);

    ui->pushButton_MainInvoices->setChecked(false);
    ui->pushButton_MainProviders->setChecked(false);
    ui->pushButton_MainClients->setChecked(false);
    ui->pushButton_MainReports->setChecked(false);
    ui->pushButton_MainStorages->setChecked(false);
    ui->pushButton_MainUsers->setChecked(false);
}

void MainWindow::slot_pushButton_MainStorages_clicked()
{
    ui->stackedWidget_MainWorkSpace->setCurrentIndex(2);

    ui->pushButton_MainInvoices->setChecked(false);
    ui->pushButton_MainProducts->setChecked(false);
    ui->pushButton_MainProviders->setChecked(false);
    ui->pushButton_MainClients->setChecked(false);
    ui->pushButton_MainReports->setChecked(false);
    ui->pushButton_MainUsers->setChecked(false);

    updateStorageTable();
}

void MainWindow::slot_pushButton_MainProviders_clicked()
{
    ui->stackedWidget_MainWorkSpace->setCurrentIndex(3);

    ui->pushButton_MainInvoices->setChecked(false);
    ui->pushButton_MainProducts->setChecked(false);
    ui->pushButton_MainClients->setChecked(false);
    ui->pushButton_MainReports->setChecked(false);
    ui->pushButton_MainStorages->setChecked(false);
    ui->pushButton_MainUsers->setChecked(false);
}

void MainWindow::slot_pushButton_MainReports_clicked()
{
    ui->stackedWidget_MainWorkSpace->setCurrentIndex(6);

    ui->pushButton_MainInvoices->setChecked(false);
    ui->pushButton_MainProducts->setChecked(false);
    ui->pushButton_MainProviders->setChecked(false);
    ui->pushButton_MainClients->setChecked(false);
    ui->pushButton_MainStorages->setChecked(false);
    ui->pushButton_MainUsers->setChecked(false);
}

void MainWindow::slot_pushButton_MainClients_clicked()
{
    ui->stackedWidget_MainWorkSpace->setCurrentIndex(4);

    ui->pushButton_MainInvoices->setChecked(false);
    ui->pushButton_MainProducts->setChecked(false);
    ui->pushButton_MainProviders->setChecked(false);
    ui->pushButton_MainReports->setChecked(false);
    ui->pushButton_MainStorages->setChecked(false);
    ui->pushButton_MainUsers->setChecked(false);
}

void MainWindow::slot_pushButton_MainUsers_clicked()
{
    ui->stackedWidget_MainWorkSpace->setCurrentIndex(5);

    ui->pushButton_MainInvoices->setChecked(false);
    ui->pushButton_MainProducts->setChecked(false);
    ui->pushButton_MainProviders->setChecked(false);
    ui->pushButton_MainClients->setChecked(false);
    ui->pushButton_MainReports->setChecked(false);
    ui->pushButton_MainStorages->setChecked(false);

    updateUserTable();
}

void MainWindow::updateStorageTable()
{
    QList <storage> listStorages = db.getListStorages();

    ui->tableWidget_Storages->setRowCount(0);

    for(int i = 0; i < listStorages.size(); i++)
    {
        ui->tableWidget_Storages->insertRow(ui->tableWidget_Storages->rowCount());
        ui->tableWidget_Storages->setItem(ui->tableWidget_Storages->rowCount()-1, 0, new QTableWidgetItem(listStorages.at(i).title));
        ui->tableWidget_Storages->setItem(ui->tableWidget_Storages->rowCount()-1, 1, new QTableWidgetItem(listStorages.at(i).city));
        ui->tableWidget_Storages->setItem(ui->tableWidget_Storages->rowCount()-1, 2, new QTableWidgetItem(listStorages.at(i).address));
        ui->tableWidget_Storages->setItem(ui->tableWidget_Storages->rowCount()-1, 3, new QTableWidgetItem(QVariant(listStorages.at(i).capacity).toString()));
        ui->tableWidget_Storages->setItem(ui->tableWidget_Storages->rowCount()-1, 4, new QTableWidgetItem(QVariant(listStorages.at(i).workload).toString()));
    }
}

void MainWindow::slot_pushButton_AddStorage_clicked()
{
    AddOrSetStorage_Dialog AddDialog;
    storage st;
    AddDialog.exec();
    st = AddDialog.getStorage();
    if(st.title.size() != 0)
    {
        db.addStorage(st);
        updateStorageTable();
    }
}

void MainWindow::updateUserTable()
{
    QList <user> listUsers = db.getListUsers();

    ui->tableWidget_Users->setRowCount(0);

    for(int i = 0; i < listUsers.size(); i++)
    {
        ui->tableWidget_Users->insertRow(ui->tableWidget_Users->rowCount());
        ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 0, new QTableWidgetItem(listUsers.at(i).pib));
        ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem(listUsers.at(i).position.title));
        ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 2, new QTableWidgetItem(listUsers.at(i).login));
        ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 3, new QTableWidgetItem(listUsers.at(i).phonenumber));
    }
}

void MainWindow::slot_pushButton_AddUser_clicked()
{
    AddOrSetUser_Dialog AddDialog;
    user us;
    AddDialog.setConnection(db);
    AddDialog.exec();
    us = AddDialog.getUser();
    if(us.login.size() != 0)
    {
        db.addUser(us);
        updateUserTable();
    }
}
