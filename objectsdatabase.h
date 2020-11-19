#ifndef OBJECTSDATABASE_H
#define OBJECTSDATABASE_H

#include <QDate>
#include <QString>

struct product
{
    int id;
    QString nomenclature;
    QString title;
    QString measuring;
    float price;
    float priceSender;
    int quantity;
};

struct typeInvoice
{
    int id;
    QString title;
};

struct storage
{
    int id;
    QString title;
    QString city;
    QString address;
    int capacity;
    int workload;

    QList <product> listProducts;
};

struct client
{
    int id;
    QString title;
    QString pib;
    QString phonenumber;
};

struct provider
{
    int id;
    QString title;
    QString pib;
    QString phonenumber;
    QString requisites;
};

struct position
{
    int id;
    QString title;
};

struct user
{
    int id;
    QString login;
    QString password;
    QString pib;
    QString phonenumber;
    position position;

    QList <storage> listStorages;
};

struct paymenttype
{
    int id;
    QString title;
};

struct invoice
{
    int id;
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
