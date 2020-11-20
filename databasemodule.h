#ifndef DATABASEMODULE_H
#define DATABASEMODULE_H

#include "objectsdatabase.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

struct resultQuery
{
    bool flag;
    QString message;
};

class DatabaseModule
{
    QSqlDatabase db;
    user connectedUser;

public:
    DatabaseModule();

    bool setDatabaseConnection(QSqlDatabase db_connection, user user_connection);
    int getPrivileges();

    resultQuery addInvoice(invoice invoice);
    resultQuery addStorage(storage storage);
    resultQuery addProduct(product product);

    resultQuery addUser(user user);
    resultQuery addProvider(provider provider);
    resultQuery addClient(client client);

    invoice getInvoiceById(int id);
    user getUserById(int id);
    client getClientById(int id);
    storage getStorageById(int id);
    provider getProviderById(int id);
    typeInvoice getTypeInvoiceById(int id);
    paymenttype getPaymentTypeById(int id);
    storno getStornoByIdInvoice(int idInvoice);
    position getPositionById(int id);
    product getProductById(int id);

    QList <product> getListProductByIdStorage(int idStorage);
    QList <product> getListProductByIdInvoice(int idInvoice);
    QList <product> getListProducts();

    QList <storage> getListStorages();

    QList <position> getListPositions();

    QList <client> getListClients();

    QList <provider> getListProviders();

    QList <invoice> getListInvoiceByType(int idType);
    QList <invoice> getListInvoiceByType(int idType, int idStorage);
    QList <invoice> getListInvoiceByTypeAvialableConnectedUser(int idType);
    QList <storno> getStornedInvoices();

    QList <user> getListUsers();
};

#endif // DATABASEMODULE_H
