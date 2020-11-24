#ifndef OBJECTSDATABASE_H
#define OBJECTSDATABASE_H

#include <QDate>
#include <QString>

struct product
{
    int id = 0;
    QString nomenclature;
    QString title;
    QString measuring;
    float price;
    float priceSender;
    int quantity = 0;
};

struct typeInvoice
{
    int id = 0;
    QString title;
};

struct storage
{
    int id = 0;
    QString title;
    QString city;
    QString address;
    int capacity;
    int workload;

    QList <product> listProducts;
};

struct client
{
    int id = 0;
    QString title;
    QString pib;
    QString phonenumber;
};

struct provider
{
    int id = 0;
    QString title;
    QString pib;
    QString phonenumber;
    QString requisites;
};

struct position
{
    int id = 0;
    QString title;
};

struct user
{
    int id = 0;
    QString login;
    QString password;
    QString pib;
    QString phonenumber;
    position position;

    QList <storage> listStorages;
};

struct paymenttype
{
    int id = 0;
    QString title;
};

struct invoice
{
    int id = 0;
    float sum;
    QDate data;
    int storno;
    QString note;

    typeInvoice typeInvoice;
    storage storageSender;
    storage storageRecipient;
    client client;
    user userSender;
    user userRecipient;
    paymenttype paymentType;
    provider provider;

    QList <product> listProducts;
};

struct storno
{
    invoice invoice;
    QString note;
};

#endif // OBJECTSDATABASE_H
