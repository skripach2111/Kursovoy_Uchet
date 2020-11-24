#ifndef DATABASEMODULE_H
#define DATABASEMODULE_H

#include "objectsdatabase.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

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

    resultQuery addStorno(storno storno);

    resultQuery setInvoice(invoice invoice);
    resultQuery setStorage(storage storage);
    resultQuery setProduct(product product);

    resultQuery setUser(user user);
    resultQuery setProvider(provider provider);
    resultQuery setClient(client client);

    resultQuery deleteInvoice(invoice invoice);
    resultQuery deleteStorage(storage storage);
    resultQuery deleteProduct(product product);

    resultQuery deleteUser(user user);
    resultQuery deleteProvider(provider provider);
    resultQuery deleteClient(client client);

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

    int getNextIdInvoice();

    QList <product> getListProductByIdStorage(int idStorage);
    QList <product> getListProductByIdInvoice(int idInvoice);
    QList <product> getListProductByTypeInvoice(int type);
    QList <product> getListProducts();

    QList <storage> getListStorages();

    QList <position> getListPositions();

    QList <client> getListClients();

    QList <provider> getListProviders();

    QList <invoice> getListInvoiceByType(int idType);
    QList <invoice> getListInvoicesByTypeAndDate(int idType, QDate begin, QDate end);
    QList <invoice> getListInvoiceByType(int idType, int idStorage);
    QList <invoice> getListInvoiceByTypeAvialableConnectedUser(int idType);
    QList <invoice> getRepordByComingInvoices(QDate begin, QDate end);
    QList <invoice> getRepordBySaleInvoices(QDate begin, QDate end);

    QList <product> getReportByPopularProduct();
    QList <product> getReportByRatingProduct();
    QList <product> getReportBySaleProduct(QDate begin, QDate end);

    QList <storno> getListStornedInvoices();
    QList <storno> getListStornedInvoicesAvialableSelectedUser();

    QList <user> getListUsers();
    QList <user> getListUsersByPosition(int id_position);

    float getPriceComingByIdProduct(int id);
};

#endif // DATABASEMODULE_H
