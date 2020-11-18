#ifndef DATABASEMODULE_H
#define DATABASEMODULE_H

#include "objectsdatabase.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

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
    QList <invoice> getInviceByType(int idType);
    QList <storno> getStornedInvoices();
};

#endif // DATABASEMODULE_H
