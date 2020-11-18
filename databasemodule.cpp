#include "databasemodule.h"

DatabaseModule::DatabaseModule()
{

}

bool DatabaseModule::setDatabaseConnection(QSqlDatabase db_connection, user user_connection)
{
    db = db_connection;
    connectedUser = user_connection;

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("baza");
    db.setUserName("userbaza");
    db.setPassword("password");
    return db.open();
}

int DatabaseModule::getPrivileges()
{
    storage tmp_storage;

    QSqlQuery query;
    query.prepare("SELECT id, pib, phonenumber, idPosition FROM users WHERE login = :login");
    query.bindValue(":login", QVariant(connectedUser.login).toString());
    query.exec();

    if(!query.size())
        return 0;
    else
    {
        connectedUser.id = query.value(1).toInt();
        connectedUser.pib = query.value(2).toString();
        connectedUser.phonenumber = query.value(3).toString();
        connectedUser.position.id = query.value(4).toInt();

        query.prepare("SELECT * FROM storage WHERE :id = (SELECT * FROM user_storage)");
        query.bindValue(":id", connectedUser.id);
        query.exec();

        while(query.next())
        {
            tmp_storage.id = query.value(1).toInt();
            tmp_storage.title = query.value(2).toString();
            tmp_storage.city = query.value(3).toString();
            tmp_storage.address = query.value(4).toString();
            tmp_storage.capacity = query.value(5).toFloat();

            connectedUser.listStorages.push_back(tmp_storage);
        }

        query.prepare("SELECT title FROM storage WHERE :id = id");
        query.bindValue(":id", connectedUser.position.id);
        query.exec();

        connectedUser.position.title = query.value(1).toString();
    }

    return connectedUser.position.id;
}

resultQuery DatabaseModule::addUser(user user)
{
    resultQuery result;

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE login = :login");
    query.bindValue(":login", QVariant(user.login).toString());
    query.exec();

    if(query.size())
    {
        result.message = "Пользователь с таким логином уже существует.";
        result.flag = false;
        return result;
    }
    else
    {
        query.prepare("INSERT INTO users (login, password, PIB, phonenumber, idPosition) VALUES(:login, :password, :PIB, :phonenumber, :idPosition)");
        query.bindValue(":login", QVariant(user.login).toString());
        query.bindValue(":password", QVariant(user.password).toString());
        query.bindValue(":PIB", QVariant(user.pib).toString());
        query.bindValue(":phonenumber", QVariant(user.phonenumber).toString());
        query.bindValue(":idPosition", user.position.id);

        if(user.listStorages.size() != 0)
        {
            query.prepare("SELECT id FROM users WHERE login = :login");
            query.bindValue(":login", QVariant(user.login).toString());
            query.exec();
            user.id = query.value(1).toInt();

            query.prepare("INSERT user_storage VALUES(:idUser, :idStorage)");

            for(int i = 0; i < user.listStorages.size(); i++)
            {
                query.bindValue(":idUser", user.id);
                query.bindValue(":idStorage", user.listStorages.at(i).id);
                query.exec();
            }
        }

        result.flag = true;
        result.message = "Пользователь добавлен.";
        return result;
    }
}

resultQuery DatabaseModule::addClient(client client)
{
    resultQuery result;

    QSqlQuery query;
    query.prepare("SELECT id FROM clients WHERE title = :title");
    query.bindValue(":title", QVariant(client.title).toString());
    query.exec();

    if(query.size())
    {
        result.message = "Клиент с таким наименованием уже существует.";
        result.flag = false;
        return result;
    }
    else
    {
        query.prepare("INSERT INTO clients (PIB, phonenumber, title) VALUES(:PIB, :phonenumber, :title)");
        query.bindValue(":PIB", QVariant(client.pib).toString());
        query.bindValue(":phonenumber", QVariant(client.phonenumber).toString());
        query.bindValue(":title", QVariant(client.title).toString());

        result.flag = true;
        result.message = "Клиент добавлен.";
        return result;
    }
}

resultQuery DatabaseModule::addProvider(provider provider)
{
    resultQuery result;

    QSqlQuery query;
    query.prepare("SELECT id FROM providers WHERE title = :title");
    query.bindValue(":title", QVariant(provider.title).toString());
    query.exec();

    if(query.size())
    {
        result.message = "Поставщик с таким наименованием уже существует.";
        result.flag = false;
        return result;
    }
    else
    {
        query.prepare("INSERT INTO providers (title, PIB, phonenumber, requisites) VALUES(:title, :PIB, :phonenumber, :requisites)");
        query.bindValue(":title", QVariant(provider.title).toString());
        query.bindValue(":PIB", QVariant(provider.pib).toString());
        query.bindValue(":phonenumber", QVariant(provider.phonenumber).toString());
        query.bindValue(":requisites", QVariant(provider.requisites).toString());

        result.flag = true;
        result.message = "Поставщик добавлен.";
        return result;
    }
}

resultQuery DatabaseModule::addStorage(storage storage)
{
    resultQuery result;

    QSqlQuery query;
    query.prepare("SELECT id FROM storage WHERE title = :title");
    query.bindValue(":title", QVariant(storage.title).toString());
    query.exec();

    if(query.size())
    {
        result.message = "Склад с таким наименованием уже существует.";
        result.flag = false;
        return result;
    }
    else
    {
        query.prepare("INSERT INTO storage (title, city, address, capacity) VALUES(:title, :city, :address, :capacity)");
        query.bindValue(":title", QVariant(storage.title).toString());
        query.bindValue(":city", QVariant(storage.city).toString());
        query.bindValue(":address", QVariant(storage.address).toString());
        query.bindValue(":capacity", storage.capacity);

        result.flag = true;
        result.message = "Склад добавлен.";
        return result;
    }
}

resultQuery DatabaseModule::addProduct(product product)
{
    resultQuery result;

    QSqlQuery query;
    query.prepare("SELECT id FROM product WHERE title = :title OR nomenclature = :nomenclature");
    query.bindValue(":title", QVariant(product.title).toString());
    query.bindValue(":nomenclature", QVariant(product.nomenclature).toString());
    query.exec();

    if(query.size())
    {
        result.message = "Такой товар уже существует.";
        result.flag = false;
        return result;
    }
    else
    {
        query.prepare("INSERT INTO storage (title, measuring, nomenclature, price) VALUES(:title, :measuring, :nomenclature, :price)");
        query.bindValue(":title", QVariant(product.title).toString());
        query.bindValue(":measuring", QVariant(product.measuring).toString());
        query.bindValue(":nomenclature", QVariant(product.nomenclature).toString());
        query.bindValue(":price", product.price);

        result.flag = true;
        result.message = "Товар добавлен.";
        return result;
    }
}

resultQuery DatabaseModule::addInvoice(invoice invoice)
{
    resultQuery result;
    QSqlQuery query;

    switch (invoice.typeInvoice.id)
    {
    case 0:
    {
        query.prepare("INSERT INTO invoices (sum, date, idTypeInvoice, idStorageRecipient, idProvider, note, storno, idUserRecipient) VALUES(:sum, :date, :idTypeInvoice, :idStorageRecipient, :idProvider, :note, 0, :idUserRecipient)");
        query.bindValue(":sum", invoice.sum);
        query.bindValue(":date", invoice.data);
        query.bindValue(":idTypeInvoice", invoice.typeInvoice.id);
        query.bindValue(":idStorageRecipient", invoice.storageRecipient.id);
        query.bindValue(":idProvider", invoice.provider.id);
        query.bindValue(":note", QVariant(invoice.note).toString());
        query.bindValue(":idUserRecipient", invoice.userRecipient.id);
        query.exec();

        query.prepare("INSERT INTO product_in_invoice VALUES(:idInvoice, :idProduct, :price, :quantity, :accounting_price)");
        for(int i = 0; i < invoice.listProducts.size(); i++)
        {
            query.bindValue(":idInvoice", invoice.id);
            query.bindValue(":idProduct", invoice.listProducts.at(i).id);
            query.bindValue(":price", invoice.listProducts.at(i).priceSender);
            query.bindValue(":quantity", invoice.listProducts.at(i).quantity);
            query.bindValue(":accounting_price", invoice.listProducts.at(i).price);
            query.exec();
        }

        break;
    }
    case 1:
    {
        query.prepare("INSERT INTO invoices (sum, date, idTypeInvoice, idStorageSender, idUserSender, idClient, note, storno, idPaymentType) VALUES(:sum, :date, :idTypeInvoice, :idStorageSender, :idClient, :note, 0, :idPaymentType)");
        query.bindValue(":sum", invoice.sum);
        query.bindValue(":date", invoice.data);
        query.bindValue(":idTypeInvoice", invoice.typeInvoice.id);
        query.bindValue(":idStorageSender", invoice.storageSender.id);
        query.bindValue(":idClient", invoice.client.id);
        query.bindValue(":note", QVariant(invoice.note).toString());
        query.bindValue(":idUserSender", invoice.userSender.id);
        query.bindValue(":idPaymentType", invoice.paymentType.id);
        query.exec();

        query.prepare("INSERT INTO product_in_invoice VALUES(:idInvoice, :idProduct, :price, :quantity)");
        for(int i = 0; i < invoice.listProducts.size(); i++)
        {
            query.bindValue(":idInvoice", invoice.id);
            query.bindValue(":idProduct", invoice.listProducts.at(i).id);
            query.bindValue(":price", invoice.listProducts.at(i).priceSender);
            query.bindValue(":quantity", invoice.listProducts.at(i).quantity);
            query.exec();
        }

        break;
    }
    case 2:
    {
        query.prepare("INSERT INTO invoices (date, idTypeInvoice, idStorageSender, idUserSender, idStorageRecipient, idUserRecipient, note, storno) VALUES(:date, :idTypeInvoice, :idStorageSender, :idUserSender, :idStorageRecipient, :idUserRecipient, :note, 0)");
        query.bindValue(":date", invoice.data);
        query.bindValue(":idTypeInvoice", invoice.typeInvoice.id);
        query.bindValue(":idUserSender", invoice.userSender.id);
        query.bindValue(":idStorageSender", invoice.storageSender.id);
        query.bindValue(":idUserRecipient", invoice.userRecipient.id);
        query.bindValue(":idStorageRecipient", invoice.storageRecipient.id);
        query.bindValue(":note", QVariant(invoice.note).toString());
        query.exec();

        query.prepare("INSERT INTO product_in_invoice VALUES(:idInvoice, :idProduct, :quantity)");
        for(int i = 0; i < invoice.listProducts.size(); i++)
        {
            query.bindValue(":idInvoice", invoice.id);
            query.bindValue(":idProduct", invoice.listProducts.at(i).id);
            query.bindValue(":quantity", invoice.listProducts.at(i).quantity);
            query.exec();
        }

        break;
    }
    }

    result.flag = true;
    result.message = "Накладная добавлена.";
    return result;
}
