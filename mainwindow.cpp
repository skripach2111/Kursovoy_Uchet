#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget_3->removeTab(1);
    ui->tabWidget_Invoices->removeTab(4);

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

    connect(ui->pushButton_ToFormedReportDeliveryReport, SIGNAL(clicked()), this, SLOT(slot_pushButton_ToFormedReportDeliveryReport_clicked()));
    connect(ui->pushButton_ReportBySalesForm, SIGNAL(clicked()), this, SLOT(slot_pushButton_ReportBySalesForm_clicked()));
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
//        ui->tableWidget_Storages->setItem(ui->tableWidget_Storages->rowCount()-1, 4, new QTableWidgetItem(QVariant(listStorages.at(i).workload).toString()));
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
    QList <product> listProducts = db.getListProducts();
    //    QList <storage> listStorage = db.getListStorages();
    //    bool flag = true;

    //    listProducts += listStorage.at(0).listProducts;

    //    for(int i = 1; i < listStorage.size(); i++)
    //    {
    //        for(int j = 0; j < listStorage.at(i).listProducts.size(); j++)
    //        {
    //            for(int k = 0; k < listProducts.size(); k++)
    //            {
    //                if(listStorage.at(i).listProducts.at(j).id == listProducts.at(k).id)
    //                {
    //                    listProducts[k].quantity += listStorage.at(i).listProducts.at(j).quantity;
    //                    k = listProducts.size();
    //                    flag = false;
    //                }
    //            }

    //            if(flag)
    //            {
    //                listProducts.push_back(listStorage.at(i).listProducts.at(j));
    //            }

    //            flag = true;
    //        }
    //    }

    ui->tableWidget_Products->setRowCount(0);

    for(int i = 0; i < listProducts.size(); i++)
    {
        ui->tableWidget_Products->insertRow(ui->tableWidget_Products->rowCount());
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 0, new QTableWidgetItem(listProducts.at(i).nomenclature));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 1, new QTableWidgetItem(listProducts.at(i).title));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 2, new QTableWidgetItem(listProducts.at(i).measuring));
        //        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 3, new QTableWidgetItem(listProducts.at(i).quantity));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 3, new QTableWidgetItem(QVariant(listProducts.at(i).price).toString()));
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
        ui->stackedWidget_ControlButtons->setVisible(true);
        updateComingInvoicesTable();
        break;
    }
    case 1:
    {
        ui->stackedWidget_ControlButtons->setVisible(true);
        updateSenderInvoicesTable();
        break;
    }
    case 2:
    {
        ui->stackedWidget_ControlButtons->setVisible(true);
        updateMovingInvoicesTable();
        break;
    }
    case 3:
    {
        ui->stackedWidget_ControlButtons->setVisible(false);
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
        ui->tableWidget_stornoInvoices->setItem(ui->tableWidget_stornoInvoices->rowCount()-1, 0, new QTableWidgetItem(QVariant(listInvoices.at(i).invoice.id).toString()));
        ui->tableWidget_stornoInvoices->setItem(ui->tableWidget_stornoInvoices->rowCount()-1, 1, new QTableWidgetItem(listInvoices.at(i).invoice.typeInvoice.title));
        ui->tableWidget_stornoInvoices->setItem(ui->tableWidget_stornoInvoices->rowCount()-1, 2, new QTableWidgetItem(listInvoices.at(i).invoice.data.toString(Qt::LocalDate)));
        //        ui->tableWidget_stornoInvoices->setItem(ui->tableWidget_stornoInvoices->rowCount()-1, 3, new QTableWidgetItem(listInvoices.at(i).note));
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
    AddDialog.setClient(db.getClientById(ui->tableWidget_Clients->selectedItems().at(0)->row()+1));
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

void MainWindow::slot_pushButton_ToFormedReportDeliveryReport_clicked()
{
    QList <invoice> listInvoices = db.getRepordByComingInvoices(ui->calendarWidge_PeriodBegin->selectedDate(), ui->calendarWidget_PeriodEnd->selectedDate());
    QList <product> listProducts;
    bool flag = true;

    listProducts += listInvoices.at(0).listProducts;

    for(int i = 1; i < listInvoices.size(); i++)
    {
        for(int j = 0; j < listInvoices.at(i).listProducts.size(); j++)
        {
            for(int k = 0; k < listProducts.size(); k++)
            {
                if(listInvoices.at(i).listProducts.at(j).id == listProducts.at(k).id)
                {
                    listProducts[k].quantity += listInvoices.at(i).listProducts.at(j).quantity;
                    k = listProducts.size();
                    flag = false;
                }
            }

            if(flag)
            {
                listProducts.push_back(listInvoices.at(i).listProducts.at(j));
            }

            flag = true;
        }
    }

    ui->tableWidget_ProductInDeliveryReport->setRowCount(0);

    for(int i = 0; i < listProducts.size(); i++)
    {
        ui->tableWidget_ProductInDeliveryReport->insertRow(ui->tableWidget_ProductInDeliveryReport->rowCount());
        ui->tableWidget_ProductInDeliveryReport->setItem(ui->tableWidget_ProductInDeliveryReport->rowCount()-1, 0, new QTableWidgetItem(listProducts.at(i).nomenclature));
        ui->tableWidget_ProductInDeliveryReport->setItem(ui->tableWidget_ProductInDeliveryReport->rowCount()-1, 1, new QTableWidgetItem(listProducts.at(i).title));
        ui->tableWidget_ProductInDeliveryReport->setItem(ui->tableWidget_ProductInDeliveryReport->rowCount()-1, 2, new QTableWidgetItem(QVariant(listProducts.at(i).quantity).toString()));
        ui->tableWidget_ProductInDeliveryReport->setItem(ui->tableWidget_ProductInDeliveryReport->rowCount()-1, 3, new QTableWidgetItem(listProducts.at(i).measuring));
        ui->tableWidget_ProductInDeliveryReport->setItem(ui->tableWidget_ProductInDeliveryReport->rowCount()-1, 4, new QTableWidgetItem(QVariant(listProducts.at(i).priceSender).toString()));
        ui->tableWidget_ProductInDeliveryReport->setItem(ui->tableWidget_ProductInDeliveryReport->rowCount()-1, 5, new QTableWidgetItem(QVariant(listProducts.at(i).priceSender*listProducts.at(i).quantity).toString()));
    }

    int sum = 0;
    int number = 0;

    for(int i = 0; i < listProducts.size(); i++)
    {
        sum += listProducts.at(i).quantity*listProducts.at(i).priceSender;
        number += listProducts.at(i).quantity;
    }

    ui->label_NumberProductsInDeliveryReport->setText(QVariant(number).toString());
    ui->label_SumInDeliveryReport->setText(QVariant(sum).toString());
    ui->label_TimePriodInDeliveryReport->setText("с " + ui->calendarWidge_PeriodBegin->selectedDate().toString(Qt::LocalDate) + " по " + ui->calendarWidget_PeriodEnd->selectedDate().toString(Qt::LocalDate));
}

void MainWindow::slot_pushButton_ReportBySalesForm_clicked()
{
    QList <invoice> listInvoices = db.getRepordBySaleInvoices(ui->calendarWidget_PeriodSaleBegin->selectedDate(), ui->calendarWidget_PeriodSaleEnd->selectedDate());
    QList <product> listProducts;
    bool flag = true;

    listProducts += listInvoices.at(0).listProducts;

    for(int i = 1; i < listInvoices.size(); i++)
    {
        for(int j = 0; j < listInvoices.at(i).listProducts.size(); j++)
        {
            for(int k = 0; k < listProducts.size(); k++)
            {
                if(listInvoices.at(i).listProducts.at(j).id == listProducts.at(k).id)
                {
                    listProducts[k].quantity += listInvoices.at(i).listProducts.at(j).quantity;
                    k = listProducts.size();
                    flag = false;
                }
            }

            if(flag)
            {
                listProducts.push_back(listInvoices.at(i).listProducts.at(j));
            }

            flag = true;
        }
    }

    ui->tableWidget_ProductsInSaleReport->setRowCount(0);

    for(int i = 0; i < listProducts.size(); i++)
    {
        ui->tableWidget_ProductsInSaleReport->insertRow(ui->tableWidget_ProductsInSaleReport->rowCount());
        ui->tableWidget_ProductsInSaleReport->setItem(ui->tableWidget_ProductsInSaleReport->rowCount()-1, 0, new QTableWidgetItem(listProducts.at(i).nomenclature));
        ui->tableWidget_ProductsInSaleReport->setItem(ui->tableWidget_ProductsInSaleReport->rowCount()-1, 1, new QTableWidgetItem(listProducts.at(i).title));
        ui->tableWidget_ProductsInSaleReport->setItem(ui->tableWidget_ProductsInSaleReport->rowCount()-1, 2, new QTableWidgetItem(QVariant(listProducts.at(i).quantity).toString()));
        ui->tableWidget_ProductsInSaleReport->setItem(ui->tableWidget_ProductsInSaleReport->rowCount()-1, 3, new QTableWidgetItem(listProducts.at(i).measuring));
        ui->tableWidget_ProductsInSaleReport->setItem(ui->tableWidget_ProductsInSaleReport->rowCount()-1, 4, new QTableWidgetItem(QVariant(listProducts.at(i).price).toString()));
        ui->tableWidget_ProductsInSaleReport->setItem(ui->tableWidget_ProductsInSaleReport->rowCount()-1, 5, new QTableWidgetItem(QVariant(listProducts.at(i).price*listProducts.at(i).quantity).toString()));
    }

    int sum = 0;
    int number = 0;

    for(int i = 0; i < listProducts.size(); i++)
    {
        sum += listProducts.at(i).quantity*listProducts.at(i).price;
        number += listProducts.at(i).quantity;
    }

    ui->label_NumberProductsInSaleReport->setText(QVariant(number).toString());
    ui->label_SumInSaleReport->setText(QVariant(sum).toString());
    ui->label_label_TimePriodInSaleReport->setText("с " + ui->calendarWidget_PeriodSaleBegin->selectedDate().toString(Qt::LocalDate) + " по " + ui->calendarWidget_PeriodSaleEnd->selectedDate().toString(Qt::LocalDate));
}

void MainWindow::on_pushButton_PopularityTableForm_clicked()
{
    QList <product> listProducts = db.getReportByPopularProduct();

    ui->tableWidget_PopularityTable->setRowCount(0);

    for(int i = 0; i < listProducts.size(); i++)
    {
        ui->tableWidget_PopularityTable->insertRow(ui->tableWidget_PopularityTable->rowCount());
        ui->tableWidget_PopularityTable->setItem(ui->tableWidget_PopularityTable->rowCount()-1, 0, new QTableWidgetItem(listProducts.at(i).nomenclature));
        ui->tableWidget_PopularityTable->setItem(ui->tableWidget_PopularityTable->rowCount()-1, 1, new QTableWidgetItem(listProducts.at(i).title));
        ui->tableWidget_PopularityTable->setItem(ui->tableWidget_PopularityTable->rowCount()-1, 2, new QTableWidgetItem(QVariant(listProducts.at(i).quantity).toString()));
    }
}

void MainWindow::on_pushButton_FinancialReportForm_clicked()
{
    QList <product> listProducts = db.getReportBySaleProduct(ui->calendarWidget_FinancialReportPeriodBegin->selectedDate(), ui->calendarWidget_FinancialReportPeriodEnd->selectedDate());

    float sumComing = 0;
    float sumSale = 0;
    int number = 0;
    float benefit = 0;

    for(int i = 0; i < listProducts.size(); i++)
        number += listProducts.at(i).quantity;

    for(int i = 0; i < listProducts.size(); i++)
        sumComing += listProducts.at(i).quantity*listProducts.at(i).priceSender;

    for(int i = 0; i < listProducts.size(); i++)
        sumSale += listProducts.at(i).quantity*listProducts.at(i).price;

    benefit = sumSale - sumComing;

    ui->label_FinancialReportPeriod->setText("с " + ui->calendarWidget_FinancialReportPeriodBegin->selectedDate().toString(Qt::LocalDate) + " по " + ui->calendarWidget_FinancialReportPeriodEnd->selectedDate().toString(Qt::LocalDate));
    ui->label_FinancialReportNumberSaleProduct->setText(QVariant(number).toString());
    ui->label_SumCostSalePurchase->setText(QVariant(sumComing).toString());
    ui->label_SumCostSale->setText(QVariant(sumSale).toString());
    ui->label_SumBenefit->setText(QVariant(benefit).toString());
}

void MainWindow::on_pushButton_StornInvoice_clicked()
{
    storno st;

    switch (ui->tabWidget_Invoices->currentIndex())
    {
    case 0:
    {
        qDebug() << ui->tableWidget_comingInvoices->selectedItems().at(0)->text().toInt();
        st.invoice = db.getInvoiceById(ui->tableWidget_comingInvoices->selectedItems().at(0)->text().toInt());
        break;
    }
    case 1:
    {
        qDebug() << ui->tableWidget_careInvoices->selectedItems().at(0)->text().toInt();
        st.invoice = db.getInvoiceById(ui->tableWidget_careInvoices->selectedItems().at(0)->text().toInt());
        break;
    }
    case 2:
    {
        st.invoice = db.getInvoiceById(ui->tableWidget_movingInvoices->selectedItems().at(0)->text().toInt());
        break;
    }
    }

    db.addStorno(st);
    updateStornedInvoicesTable();
}

void MainWindow::on_pushButton_MoreAboutInvoice_clicked()
{
    MoreAboutInvoice_Dialog MoreDialog;
    invoice inv;

    switch (ui->tabWidget_Invoices->currentIndex())
    {
    case 0:
    {
        inv = db.getInvoiceById(ui->tableWidget_comingInvoices->selectedItems().at(0)->text().toInt());
        break;
    }
    case 1:
    {
        inv = db.getInvoiceById(ui->tableWidget_careInvoices->selectedItems().at(0)->text().toInt());
        break;
    }
    case 2:
    {
        inv = db.getInvoiceById(ui->tableWidget_movingInvoices->selectedItems().at(0)->text().toInt());
        break;
    }
    }

    MoreDialog.setDialog(inv);
    MoreDialog.exec();
}

void MainWindow::on_pushButton_PrintDeliveryReport_clicked()
{
    QString textForCheck;
    QString textForDocument;

    textForCheck = "\t\t\tПоставки\t\t\t\n\t\t\t"+ui->label_TimePriodInDeliveryReport->text()+"\t\t\t\n";
    textForCheck += "######################################################################\n";
    textForCheck += "Номенклатура\t Наименование\t Количество\t Ед.изм.\t Цена за ед.\t Сумма\n";
    textForCheck += "######################################################################\n";

    ui->tableWidget_ProductInDeliveryReport->selectAll();

    for(int i = 0; i < ui->tableWidget_ProductInDeliveryReport->rowCount(); i++)
    {
        textForCheck += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i)->text()+"\t";
        textForCheck += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i+1)->text()+"\t";
        textForCheck += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i+2)->text()+"\t";
        textForCheck += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i+3)->text()+"\t";
        textForCheck += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i+4)->text()+"\t";
        textForCheck += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i+5)->text()+"\t\n";
    }

    textForCheck += "######################################################################\n";

    textForCheck += "\nОбщее количество: " + ui->label_NumberProductsInDeliveryReport->text();
    textForCheck += "\nОбщая сумма: " + ui->label_SumInDeliveryReport->text();
    textForCheck += "\n####################################################################\n";

    textForDocument = "\t\t\tПоставки\t\t\t\n\t\t\t"+ui->label_TimePriodInDeliveryReport->text()+"\t\t\t\n";
    textForDocument += "\n";
    textForDocument += "Номенклатура\t Наименование\t Количество\t Ед.изм.\t Цена за ед.\t Сумма\n";
    textForDocument += "\n";

    for(int i = 0; i < ui->tableWidget_ProductInDeliveryReport->rowCount(); i++)
    {
        textForDocument += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i)->text()+"\t";
        textForDocument += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i+1)->text()+"\t";
        textForDocument += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i+2)->text()+"\t";
        textForDocument += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i+3)->text()+"\t";
        textForDocument += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i+4)->text()+"\t";
        textForDocument += ui->tableWidget_ProductInDeliveryReport->selectedItems().at(i+5)->text()+"\t\n";
    }

    textForDocument += "\n";

    textForDocument += "\nОбщее количество: " + ui->label_NumberProductsInDeliveryReport->text();
    textForDocument += "\nОбщая сумма: " + ui->label_SumInDeliveryReport->text();
    textForDocument += "\n";

    PrintPreview_Dialog preview;
    preview.setDialog(textForCheck, textForDocument);
    preview.exec();
}

void MainWindow::on_pushButton_PrintSaleReport_clicked()
{
    QString textForCheck;
    QString textForDocument;

    textForCheck = "\t\t\Продажи\t\t\t\n\t\t\t"+ui->label_label_TimePriodInSaleReport->text()+"\t\t\t\n";
    textForCheck += "######################################################################\n";
    textForCheck += "Номенклатура\t Наименование\t Количество\t Ед.изм.\t Цена за ед.\t Сумма\n";
    textForCheck += "######################################################################\n";

    ui->tableWidget_ProductsInSaleReport->selectAll();

    for(int i = 0; i < ui->tableWidget_ProductsInSaleReport->rowCount(); i++)
    {
        textForCheck += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i)->text()+"\t";
        textForCheck += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i+1)->text()+"\t";
        textForCheck += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i+2)->text()+"\t";
        textForCheck += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i+3)->text()+"\t";
        textForCheck += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i+4)->text()+"\t";
        textForCheck += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i+5)->text()+"\t\n";
    }

    textForCheck += "######################################################################\n";

    textForCheck += "\nОбщее количество: " + ui->label_NumberProductsInSaleReport->text();
    textForCheck += "\nОбщая сумма: " + ui->label_SumInSaleReport->text();
    textForCheck += "\n####################################################################\n";

    textForDocument = "\t\t\tПоставки\t\t\t\n\t\t\t"+ui->label_TimePriodInDeliveryReport->text()+"\t\t\t\n";
    textForDocument += "\n";
    textForDocument += "Номенклатура\t Наименование\t Количество\t Ед.изм.\t Цена за ед.\t Сумма\n";
    textForDocument += "\n";

    for(int i = 0; i < ui->tableWidget_ProductInDeliveryReport->rowCount(); i++)
    {
        textForDocument += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i)->text()+"\t";
        textForDocument += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i+1)->text()+"\t";
        textForDocument += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i+2)->text()+"\t";
        textForDocument += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i+3)->text()+"\t";
        textForDocument += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i+4)->text()+"\t";
        textForDocument += ui->tableWidget_ProductsInSaleReport->selectedItems().at(i+5)->text()+"\t\n";
    }

    textForDocument += "\n";

    textForDocument += "\nОбщее количество: " + ui->label_NumberProductsInSaleReport->text();
    textForDocument += "\nОбщая сумма: " + ui->label_SumInSaleReport->text();
    textForDocument += "\n";

    PrintPreview_Dialog preview;
    preview.setDialog(textForCheck, textForDocument);
    preview.exec();
}

void MainWindow::on_pushButton_PopularityTablePrint_clicked()
{
    QString textForCheck;
    QString textForDocument;

    textForCheck += "###########################################\n";
    textForCheck += "Номенклатура\t Наименование\t Количество\n";
    textForCheck += "###########################################\n";

    ui->tableWidget_PopularityTable->selectAll();

    for(int i = 0; i < ui->tableWidget_PopularityTable->rowCount(); i++)
    {
        textForCheck += ui->tableWidget_PopularityTable->selectedItems().at(i)->text()+"\t";
        textForCheck += ui->tableWidget_PopularityTable->selectedItems().at(i+1)->text()+"\t";
        textForCheck += ui->tableWidget_PopularityTable->selectedItems().at(i+2)->text()+"\t\n";
    }

    textForCheck += "###########################################\n";

    textForDocument += "\n";
    textForDocument += "Номенклатура\t Наименование\t Количество\n";
    textForDocument += "\n";

    for(int i = 0; i < ui->tableWidget_PopularityTable->rowCount(); i++)
    {
        textForDocument += ui->tableWidget_PopularityTable->selectedItems().at(i)->text()+"\t";
        textForDocument += ui->tableWidget_PopularityTable->selectedItems().at(i+1)->text()+"\t";
        textForDocument += ui->tableWidget_PopularityTable->selectedItems().at(i+2)->text()+"\t\n";
    }

    textForDocument += "\n";

    PrintPreview_Dialog preview;
    preview.setDialog(textForCheck, textForDocument);
    preview.exec();
}

void MainWindow::on_pushButton_FinancialReportPrint_clicked()
{
    QString textForCheck;
    QString textForDocument;

    textForCheck = "\t\t\Отчёт\n\t\t"+ui->label_FinancialReportPeriod->text()+"\t\t\t\n";


    textForCheck += "#########################################\n";
    textForCheck += "Общее количество проданного товара: " + ui->label_FinancialReportNumberSaleProduct->text();
    textForCheck += "\nОбщая стоимость проданного товара при закупке: " + ui->label_SumCostSalePurchase->text();
    textForCheck += "\nОбщая стоимость проданного товара при продаже: " + ui->label_SumCostSale->text();
    textForCheck += "\nСуммарная выгода с проданного товара: " + ui->label_SumBenefit->text();
    textForCheck += "\n#######################################\n";

    textForDocument = "\t\t\Отчёт\n\t\t"+ui->label_FinancialReportPeriod->text()+"\t\t\t\n";
    textForDocument += "\nОбщее количество проданного товара: " + ui->label_FinancialReportNumberSaleProduct->text();
    textForDocument += "\nОбщая стоимость проданного товара при закупке: " + ui->label_SumCostSalePurchase->text();
    textForDocument += "\nОбщая стоимость проданного товара при продаже: " + ui->label_SumCostSale->text();
    textForDocument += "\nСуммарная выгода с проданного товара: " + ui->label_SumBenefit->text();
    textForDocument += "\n";

    PrintPreview_Dialog preview;
    preview.setDialog(textForCheck, textForDocument);
    preview.exec();
}

void MainWindow::on_pushButton_ToFormedReportDeliveryReport_clicked()
{

}
