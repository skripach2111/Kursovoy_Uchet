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
    connect(ui->pushButton_AddClient, SIGNAL(clicked()), this, SLOT(slot_pushButton_AddClient_clicked()));
    connect(ui->pushButton_AddProvider, SIGNAL(clicked()), this, SLOT(slot_pushButton_AddProvider_clicked()));
    connect(ui->pushButton_AddProduct, SIGNAL(clicked()), this, SLOT(slot_pushButton_AddProduct_clicked()));
    connect(ui->pushButton_AddInvoice, SIGNAL(clicked()), this, SLOT(slot_pushButton_AddInvoice_clicked()));

    connect(ui->pushButton_SetStorage, SIGNAL(clicked()), this, SLOT(slot_pushButton_SetStorage_clicked()));
    connect(ui->pushButton_SetUser, SIGNAL(clicked()), this, SLOT(slot_pushButton_SetUser_clicked()));
    connect(ui->pushButton_SetClient, SIGNAL(clicked()), this, SLOT(slot_pushButton_SetClient_clicked()));
    connect(ui->pushButton_SetProvider, SIGNAL(clicked()), this, SLOT(slot_pushButton_SetProvider_clicked()));
    connect(ui->pushButton_SetProduct, SIGNAL(clicked()), this, SLOT(slot_pushButton_SetProduct_clicked()));

    connect(ui->pushButton_RemoveStorage, SIGNAL(clicked()), this, SLOT(slot_pushButton_RemoveStorage_clicked()));
    connect(ui->pushButton_RemoveUser, SIGNAL(clicked()), this, SLOT(slot_pushButton_RemoveUser_clicked()));
    connect(ui->pushButton_RemoveClient, SIGNAL(clicked()), this, SLOT(slot_pushButton_RemoveClient_clicked()));
    connect(ui->pushButton_RemoveProvider, SIGNAL(clicked()), this, SLOT(slot_pushButton_RemoveProvider_clicked()));
    connect(ui->pushButton_RemoveProduct, SIGNAL(clicked()), this, SLOT(slot_pushButton_RemoveProduct_clicked()));

    connect(ui->tabWidget_Invoices, SIGNAL(currentChanged(int)), this, SLOT(slot_pushButton_tabWidget_Invoices_currentChanget(int)));
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
    //ui->pushButton_MainUsers->setVisible(false);
    ui->pushButton_AddInvoice->setVisible(false);
    ui->pushButton_StornInvoice->setVisible(false);
}

void MainWindow::updateComingInvoicesTable()
{
    QList <invoice> listInvoices;
    listInvoices = db.getListInvoiceByType(1);
    ui->tableWidget_comingInvoices->setRowCount(0);

    for(int i = 0; i < listInvoices.size(); i++)
    {
        ui->tableWidget_comingInvoices->insertRow(ui->tableWidget_comingInvoices->rowCount());
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 0, new QTableWidgetItem(QVariant(listInvoices.at(i).id).toString()));
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 1, new QTableWidgetItem(QVariant(listInvoices.at(i).provider.title).toString()));
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 2, new QTableWidgetItem(listInvoices.at(i).storageRecipient.title));
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 3, new QTableWidgetItem(QVariant(listInvoices.at(i).sum).toString()));
        ui->tableWidget_comingInvoices->setItem(ui->tableWidget_comingInvoices->rowCount()-1, 4, new QTableWidgetItem(listInvoices.at(i).data.toString(Qt::LocalDate)));
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
    updateComingInvoicesTable();
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

    updateProductTable();
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

    updateProviderTable();
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

    updateClientTable();
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

void MainWindow::updateClientTable()
{
    QList <client> listClients = db.getListClients();

    ui->tableWidget_Clients->setRowCount(0);

    for(int i = 0; i < listClients.size(); i++)
    {
        ui->tableWidget_Clients->insertRow(ui->tableWidget_Clients->rowCount());
        ui->tableWidget_Clients->setItem(ui->tableWidget_Clients->rowCount()-1, 0, new QTableWidgetItem(listClients.at(i).title));
        ui->tableWidget_Clients->setItem(ui->tableWidget_Clients->rowCount()-1, 1, new QTableWidgetItem(listClients.at(i).pib));
        ui->tableWidget_Clients->setItem(ui->tableWidget_Clients->rowCount()-1, 2, new QTableWidgetItem(listClients.at(i).phonenumber));
    }
}

void MainWindow::slot_pushButton_AddClient_clicked()
{
    AddOrSetClient_Dialog AddDialog;
    client cl;
    AddDialog.exec();
    cl = AddDialog.getClient();
    if(cl.title.size() != 0)
    {
        db.addClient(cl);
        updateClientTable();
    }
}

void MainWindow::updateProviderTable()
{
    QList <provider> listProviders = db.getListProviders();

    ui->tableWidget_Providers->setRowCount(0);

    for(int i = 0; i < listProviders.size(); i++)
    {
        ui->tableWidget_Providers->insertRow(ui->tableWidget_Providers->rowCount());
        ui->tableWidget_Providers->setItem(ui->tableWidget_Providers->rowCount()-1, 0, new QTableWidgetItem(listProviders.at(i).title));
        ui->tableWidget_Providers->setItem(ui->tableWidget_Providers->rowCount()-1, 1, new QTableWidgetItem(listProviders.at(i).pib));
        ui->tableWidget_Providers->setItem(ui->tableWidget_Providers->rowCount()-1, 2, new QTableWidgetItem(listProviders.at(i).phonenumber));
        ui->tableWidget_Providers->setItem(ui->tableWidget_Providers->rowCount()-1, 3, new QTableWidgetItem(listProviders.at(i).requisites));
    }
}

void MainWindow::slot_pushButton_AddProvider_clicked()
{
    AddOrSetProvider_Dialog AddDialog;
    provider pr;
    AddDialog.exec();
    pr = AddDialog.getProvider();
    if(pr.title.size() != 0)
    {
        db.addProvider(pr);
        updateProviderTable();
    }
}

void MainWindow::updateProductTable()
{
    QList <product> listProducts;
    QList <storage> listStorage = db.getListStorages();
    bool flag = true;

    listProducts += listStorage.at(0).listProducts;

    for(int i = 1; i < listStorage.size(); i++)
    {
        for(int j = 0; j < listStorage.at(i).listProducts.size(); j++)
        {
            for(int k = 0; k < listProducts.size(); k++)
            {
                if(listStorage.at(i).listProducts.at(j).id == listProducts.at(k).id)
                {
                    listProducts[k].quantity += listStorage.at(i).listProducts.at(j).quantity;
                    k = listProducts.size();
                    flag = false;
                }
            }

            if(flag)
            {
                listProducts.push_back(listStorage.at(i).listProducts.at(j));
                flag = false;
            }
        }
    }

    ui->tableWidget_Products->setRowCount(0);

    for(int i = 0; i < listProducts.size(); i++)
    {
        ui->tableWidget_Products->insertRow(ui->tableWidget_Products->rowCount());
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 0, new QTableWidgetItem(listProducts.at(i).nomenclature));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 1, new QTableWidgetItem(listProducts.at(i).title));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 2, new QTableWidgetItem(listProducts.at(i).measuring));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 3, new QTableWidgetItem(listProducts.at(i).quantity));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 4, new QTableWidgetItem(listProducts.at(i).price));
    }
}

void MainWindow::slot_pushButton_AddProduct_clicked()
{
    AddOrSetProduct_Dialog AddDialog;
    product pr;
    AddDialog.exec();
    pr = AddDialog.getProduct();

    if(pr.title.size() != 0)
    {
        db.addProduct(pr);
        updateProductTable();
    }
}

void MainWindow::slot_pushButton_AddInvoice_clicked()
{
    AddInvoice_Dialog AddDialog;
    AddDialog.setDialog(db);
    AddDialog.exec();
    if(AddDialog.getInvoice().listProducts.size() > 0)
    {
        db.addInvoice(AddDialog.getInvoice());
        updateComingInvoicesTable();
        //updateSenderInvoicesTable();
        //updateMovingInvoicesTable();
        //updateStornedInvoicesTable();
    }
}

void MainWindow::slot_pushButton_tabWidget_Invoices_currentChanget(int number)
{
    switch (ui->tabWidget_Invoices->currentIndex())
    {
    case 0:
    {
        updateComingInvoicesTable();
        break;
    }
    case 1:
    {
        updateSenderInvoicesTable();
        break;
    }
    case 2:
    {
        updateMovingInvoicesTable();
        break;
    }
    case 3:
    {
        updateStornedInvoicesTable();
        break;
    }
    }
}

void MainWindow::updateSenderInvoicesTable()
{
    QList <invoice> listInvoices;
    listInvoices = db.getListInvoiceByTypeAvialableConnectedUser(2);
    ui->tableWidget_careInvoices->setRowCount(0);

    for(int i = 0; i < listInvoices.size(); i++)
    {
        ui->tableWidget_careInvoices->insertRow(ui->tableWidget_careInvoices->rowCount());
        ui->tableWidget_careInvoices->setItem(ui->tableWidget_careInvoices->rowCount()-1, 0, new QTableWidgetItem(QVariant(listInvoices.at(i).id).toString()));
        ui->tableWidget_careInvoices->setItem(ui->tableWidget_careInvoices->rowCount()-1, 1, new QTableWidgetItem(listInvoices.at(i).storageSender.title));
        ui->tableWidget_careInvoices->setItem(ui->tableWidget_careInvoices->rowCount()-1, 2, new QTableWidgetItem(listInvoices.at(i).userSender.pib));
        ui->tableWidget_careInvoices->setItem(ui->tableWidget_careInvoices->rowCount()-1, 3, new QTableWidgetItem(listInvoices.at(i).client.title));
        ui->tableWidget_careInvoices->setItem(ui->tableWidget_careInvoices->rowCount()-1, 4, new QTableWidgetItem(QVariant(listInvoices.at(i).sum).toString()));
        ui->tableWidget_careInvoices->setItem(ui->tableWidget_careInvoices->rowCount()-1, 5, new QTableWidgetItem(listInvoices.at(i).data.toString(Qt::LocalDate)));
    }
}

void MainWindow::updateMovingInvoicesTable()
{
    QList <invoice> listInvoices;
    listInvoices = db.getListInvoiceByType(3);
    ui->tableWidget_movingInvoices->setRowCount(0);

    for(int i = 0; i < listInvoices.size(); i++)
    {
        ui->tableWidget_movingInvoices->insertRow(ui->tableWidget_movingInvoices->rowCount());
        ui->tableWidget_movingInvoices->setItem(ui->tableWidget_movingInvoices->rowCount()-1, 0, new QTableWidgetItem(QVariant(listInvoices.at(i).id).toString()));
        ui->tableWidget_movingInvoices->setItem(ui->tableWidget_movingInvoices->rowCount()-1, 1, new QTableWidgetItem(listInvoices.at(i).storageRecipient.title));
        ui->tableWidget_movingInvoices->setItem(ui->tableWidget_movingInvoices->rowCount()-1, 2, new QTableWidgetItem(listInvoices.at(i).storageSender.title));
        ui->tableWidget_movingInvoices->setItem(ui->tableWidget_movingInvoices->rowCount()-1, 3, new QTableWidgetItem(listInvoices.at(i).userSender.pib));
        ui->tableWidget_movingInvoices->setItem(ui->tableWidget_movingInvoices->rowCount()-1, 4, new QTableWidgetItem(listInvoices.at(i).userRecipient.pib));
        ui->tableWidget_movingInvoices->setItem(ui->tableWidget_movingInvoices->rowCount()-1, 5, new QTableWidgetItem(listInvoices.at(i).data.toString(Qt::LocalDate)));
    }
}

void MainWindow::updateStornedInvoicesTable()
{
    QList <storno> listInvoices;
    listInvoices = db.getListStornedInvoicesAvialableSelectedUser();
    ui->tableWidget_stornoInvoices->setRowCount(0);

    for(int i = 0; i < listInvoices.size(); i++)
    {
        ui->tableWidget_stornoInvoices->insertRow(ui->tableWidget_stornoInvoices->rowCount());
        ui->tableWidget_stornoInvoices->setItem(ui->tableWidget_stornoInvoices->rowCount()-1, 0, new QTableWidgetItem(listInvoices.at(i).invoice.id));
        ui->tableWidget_stornoInvoices->setItem(ui->tableWidget_stornoInvoices->rowCount()-1, 1, new QTableWidgetItem(listInvoices.at(i).invoice.typeInvoice.title));
        ui->tableWidget_stornoInvoices->setItem(ui->tableWidget_stornoInvoices->rowCount()-1, 2, new QTableWidgetItem(listInvoices.at(i).invoice.data.toString(Qt::LocalDate)));
        ui->tableWidget_stornoInvoices->setItem(ui->tableWidget_stornoInvoices->rowCount()-1, 3, new QTableWidgetItem(listInvoices.at(i).note));
    }
}

void MainWindow::slot_pushButton_SetStorage_clicked()
{
    AddOrSetStorage_Dialog AddDialog;
    storage st;
    AddDialog.setStorage(db.getStorageById(ui->tableWidget_Storages->currentRow()+1));
    AddDialog.exec();
    st = AddDialog.getStorage();
    if(st.title.size() != 0)
    {
        db.setStorage(st);
        updateStorageTable();
    }
}

void MainWindow::slot_pushButton_SetUser_clicked()
{
    AddOrSetUser_Dialog AddDialog;
    user us;
    AddDialog.setConnection(db);
    AddDialog.setUser(db.getUserById(ui->tableWidget_Users->currentRow()+3));
    AddDialog.exec();
    us = AddDialog.getUser();
    if(us.login.size() != 0)
    {
        db.setUser(us);
        updateUserTable();
    }
}

void MainWindow::slot_pushButton_SetClient_clicked()
{
    AddOrSetClient_Dialog AddDialog;
    client cl;
    AddDialog.setClient(db.getClientById(ui->tableWidget_Clients->currentRow()+1));
    AddDialog.exec();
    cl = AddDialog.getClient();
    if(cl.title.size() != 0)
    {
        db.setClient(cl);
        updateClientTable();
    }
}

void MainWindow::slot_pushButton_SetProvider_clicked()
{
    AddOrSetProvider_Dialog AddDialog;
    provider pr;
    AddDialog.setProvider(db.getProviderById(ui->tableWidget_Providers->currentRow()+1));
    AddDialog.exec();
    pr = AddDialog.getProvider();
    if(pr.title.size() != 0)
    {
        db.setProvider(pr);
        updateProviderTable();
    }
}

void MainWindow::slot_pushButton_SetProduct_clicked()
{
    AddOrSetProduct_Dialog AddDialog;
    product pr;
    AddDialog.setProduct(db.getProductById(ui->tableWidget_Products->currentRow()+1));
    AddDialog.exec();
    pr = AddDialog.getProduct();

    if(pr.title.size() != 0)
    {
        db.setProduct(pr);
        updateProductTable();
    }
}

void MainWindow::slot_pushButton_RemoveStorage_clicked()
{
    storage st = db.getStorageById(ui->tableWidget_Storages->currentRow()+1);
    db.deleteStorage(st);
    updateStorageTable();

}

void MainWindow::slot_pushButton_RemoveUser_clicked()
{
    user us = db.getUserById(ui->tableWidget_Users->currentRow()+3);
    db.deleteUser(us);
    updateUserTable();
}

void MainWindow::slot_pushButton_RemoveClient_clicked()
{
    client cl = db.getClientById(ui->tableWidget_Clients->currentRow()+1);
    db.deleteClient(cl);
    updateClientTable();
}

void MainWindow::slot_pushButton_RemoveProvider_clicked()
{
    provider pr = db.getProviderById(ui->tableWidget_Providers->currentRow()+1);
    db.deleteProvider(pr);
    updateProviderTable();
    qDebug() << "delete";
}

void MainWindow::slot_pushButton_RemoveProduct_clicked()
{
    product pr = db.getProductById(ui->tableWidget_Products->currentRow()+1);
    db.deleteProduct(pr);
    updateProductTable();
}
