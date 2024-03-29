#include "databasemodule.h"

DatabaseModule::DatabaseModule()
{

}

bool DatabaseModule::setDatabaseConnection(QSqlDatabase db_connection, user user_connection)
{
    db = db_connection;
    connectedUser = user_connection;
    return db.open();
}

int DatabaseModule::getPrivileges()
{
    storage tmp_storage;
    db.open();

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE login = :login");
    query.bindValue(":login", QVariant(connectedUser.login).toString());
    query.exec();

    if(query.size() == 0)
        return 0;
    else
    {
        query.next();
        connectedUser = getUserById(query.value(0).toInt());
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
        query.exec();

        if(user.listStorages.size() != 0)
        {
            query.prepare("SELECT id FROM users WHERE login = :login");
            query.bindValue(":login", QVariant(user.login).toString());
            query.exec();
            query.next();
            user.id = query.value(0).toInt();

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
        query.exec();

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
        query.exec();

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
        query.exec();

        connectedUser.listStorages.push_back(storage);
        setUser(connectedUser);

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
    query.bindValue(":title", product.title);
    query.bindValue(":nomenclature", product.nomenclature);
    query.exec();

    if(query.size())
    {
        result.message = "Такой товар уже существует.";
        result.flag = false;
        return result;
    }
    else
    {
        query.prepare("INSERT INTO product (title, measuring, nomenclature, price) VALUES(:title, :measuring, :nomenclature, :price)");
        query.bindValue(":title", product.title);
        query.bindValue(":measuring", product.measuring);
        query.bindValue(":nomenclature", product.nomenclature);
        query.bindValue(":price", product.price);
        query.exec();

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
    case 1:
    {
        qDebug() << invoice.sum << invoice.data << invoice.typeInvoice.id << invoice.storageRecipient.id << invoice.provider.id << invoice.note << invoice.userRecipient.id;

        query.prepare("INSERT INTO invoices (sum, date, idTypeInvoice, idStorageRecipient, idProvider, note, storno, idUserRecipient) VALUES(:sum, :date, :idTypeInvoice, :idStorageRecipient, :idProvider, :note, 0, :idUserRecipient)");
        query.bindValue(":sum", invoice.sum);
        query.bindValue(":date", invoice.data);
        query.bindValue(":idTypeInvoice", invoice.typeInvoice.id);
        query.bindValue(":idStorageRecipient", invoice.storageRecipient.id);
        query.bindValue(":idProvider", invoice.provider.id);
        query.bindValue(":note", invoice.note);
        query.bindValue(":idUserRecipient", invoice.userRecipient.id);
        query.exec();

        query.prepare("SELECT max(id) FROM invoices");
        query.exec();
        query.next();
        invoice.id = query.value(0).toInt();

        query.prepare("INSERT INTO product_in_invoice VALUES(:idInvoice, :idProduct, :price, :quantity, :accounting_price)");
        for(int i = 0; i < invoice.listProducts.size(); i++)
        {
            qDebug() << invoice.id << invoice.listProducts.at(i).id << invoice.listProducts.at(i).priceSender << invoice.listProducts.at(i).quantity << invoice.listProducts.at(i).quantity << invoice.listProducts.at(i).price;

            query.bindValue(":idInvoice", invoice.id);
            query.bindValue(":idProduct", invoice.listProducts.at(i).id);
            query.bindValue(":price", invoice.listProducts.at(i).priceSender);
            query.bindValue(":quantity", invoice.listProducts.at(i).quantity);
            query.bindValue(":accounting_price", invoice.listProducts.at(i).price);
            query.exec();
        }

        query.prepare("INSERT INTO product_in_storage VALUES(:idInvoice, :idProduct, :quantity)");
        for(int i = 0; i < invoice.listProducts.size(); i++)
        {
            qDebug() << invoice.id << invoice.listProducts.at(i).id << invoice.listProducts.at(i).priceSender << invoice.listProducts.at(i).quantity << invoice.listProducts.at(i).quantity << invoice.listProducts.at(i).price;

            query.bindValue(":idInvoice", invoice.id);
            query.bindValue(":idProduct", invoice.listProducts.at(i).id);
            query.bindValue(":quantity", invoice.listProducts.at(i).quantity);
            query.exec();
        }

        break;
    }
    case 2:
    {
        qDebug() << invoice.sum << invoice.data << invoice.typeInvoice.id << invoice.storageSender.id << invoice.client.id << invoice.note << invoice.userSender.id << invoice.paymentType.id;

        query.prepare("INSERT INTO invoices (sum, date, idTypeInvoice, idStorageSender, idUserSender, idClient, note, storno, idPaymentType) VALUES(:sum, :date, :idTypeInvoice, :idStorageSender, :idUserSender, :idClient, :note, :storno, :idPaymentType)");
        query.bindValue(":sum", invoice.sum);
        query.bindValue(":date", invoice.data);
        query.bindValue(":idTypeInvoice", invoice.typeInvoice.id);
        query.bindValue(":idStorageSender", invoice.storageSender.id);
        query.bindValue(":idUserSender", invoice.userSender.id);
        query.bindValue(":idClient", invoice.client.id);
        query.bindValue(":note", invoice.note);
        query.bindValue(":storno", 0);
        query.bindValue(":idPaymentType", invoice.paymentType.id);
        query.exec();

        qDebug() << query.lastError().driverText();

        query.prepare("SELECT max(id) FROM invoices");
        query.exec();
        query.next();
        invoice.id = query.value(0).toInt();

        query.prepare("INSERT INTO product_in_invoice (idInvoice, idProduct, price, quantity) VALUES(:idInvoice, :idProduct, :price, :quantity)");
        for(int i = 0; i < invoice.listProducts.size(); i++)
        {
            query.bindValue(":idInvoice", invoice.id);
            query.bindValue(":idProduct", invoice.listProducts.at(i).id);
            query.bindValue(":price", invoice.listProducts.at(i).price);
            query.bindValue(":quantity", invoice.listProducts.at(i).quantity);
            query.exec();
        }

        query.prepare("INSERT INTO product_in_storage VALUES(:idInvoice, :idProduct, :quantity)");
        for(int i = 0; i < invoice.listProducts.size(); i++)
        {
            qDebug() << invoice.id << invoice.listProducts.at(i).id << invoice.listProducts.at(i).priceSender << invoice.listProducts.at(i).quantity << invoice.listProducts.at(i).quantity << invoice.listProducts.at(i).price;

            query.bindValue(":idInvoice", invoice.id);
            query.bindValue(":idProduct", invoice.listProducts.at(i).id);
            query.bindValue(":quantity", invoice.listProducts.at(i).quantity);
            query.exec();
        }

        break;
    }
    case 3:
    {
        query.prepare("INSERT INTO invoices (date, idTypeInvoice, idStorageSender, idUserSender, idStorageRecipient, idUserRecipient, note, storno) VALUES(:date, :idTypeInvoice, :idStorageSender, :idUserSender, :idStorageRecipient, :idUserRecipient, :note, 0)");
        query.bindValue(":date", invoice.data);
        query.bindValue(":idTypeInvoice", invoice.typeInvoice.id);
        query.bindValue(":idUserSender", invoice.userSender.id);
        query.bindValue(":idStorageSender", invoice.storageSender.id);
        query.bindValue(":idUserRecipient", invoice.userRecipient.id);
        query.bindValue(":idStorageRecipient", invoice.storageRecipient.id);
        query.bindValue(":note", invoice.note);
        query.exec();

        query.prepare("SELECT max(id) FROM invoices");
        query.exec();
        query.next();
        invoice.id = query.value(0).toInt();

        query.prepare("INSERT INTO product_in_invoice VALUES(:idInvoice, :idProduct, :quantity)");
        for(int i = 0; i < invoice.listProducts.size(); i++)
        {
            query.bindValue(":idInvoice", invoice.id);
            query.bindValue(":idProduct", invoice.listProducts.at(i).id);
            query.bindValue(":quantity", invoice.listProducts.at(i).quantity);
            query.exec();
        }

        query.prepare("INSERT INTO product_in_storage VALUES(:idInvoice, :idProduct, :quantity)");
        for(int i = 0; i < invoice.listProducts.size(); i++)
        {
            qDebug() << invoice.id << invoice.listProducts.at(i).id << invoice.listProducts.at(i).priceSender << invoice.listProducts.at(i).quantity << invoice.listProducts.at(i).quantity << invoice.listProducts.at(i).price;

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

typeInvoice DatabaseModule::getTypeInvoiceById(int id)
{
    typeInvoice type;

    QSqlQuery query;
    query.prepare("SELECT * FROM type_invoice WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();

    type.id = query.value(0).toInt();
    type.title = query.value(1).toString();

    return type;
}

position DatabaseModule::getPositionById(int id)
{
    position pos;

    QSqlQuery query;
    query.prepare("SELECT * FROM position WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();

    pos.id = query.value(0).toInt();
    pos.title = query.value(1).toString();

    return pos;
}

user DatabaseModule::getUserById(int id)
{
    user us;

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();

    us.id = query.value(0).toInt();
    us.login = query.value(1).toString();
    us.password = query.value(2).toString();
    us.pib = query.value(3).toString();
    us.phonenumber = query.value(4).toString();
    us.position = getPositionById(query.value(5).toInt());

    QSqlQuery qu2;
    qu2.prepare("SELECT idStorage FROM user_storage WHERE idUser = :idUser");
    qu2.bindValue(":idUser", us.id);
    qu2.exec();

    while(qu2.next())
        us.listStorages.push_back(getStorageById(qu2.value(0).toInt()));

    return us;
}

provider DatabaseModule::getProviderById(int id)
{
    provider pr;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM providers WHERE id = :id");
    qu.bindValue(":id", id);
    qu.exec();
    qu.next();

    pr.id = qu.value(0).toInt();
    pr.title = qu.value(1).toString();
    pr.pib = qu.value(2).toString();
    pr.phonenumber = qu.value(3).toString();
    pr.requisites = qu.value(4).toString();

    return pr;
}

QList <product> DatabaseModule::getListProductByIdStorage(int idStorage)
{
    QList <product> listProducts;
    product pr;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM product WHERE id = (SELECT idProduct FROM product_in_storage WHERE idStorage = :idStorage)");
    qu.bindValue(":idStorage", idStorage);
    qu.exec();

    QSqlQuery qu2;
    qu2.prepare("SELECT quantity FROM product_in_storage WHERE idProduct = :idProduct AND idStorage = :idStorage");
    qu2.bindValue(":idStorage", idStorage);

    while(qu.next())
    {
        pr.id = qu.value(0).toInt();
        pr.title = qu.value(1).toString();
        pr.measuring = qu.value(2).toString();
        pr.nomenclature = qu.value(3).toString();
        pr.price = qu.value(4).toFloat();

        qu2.bindValue(":idProduct", pr.id);
        qu2.exec();
        qu2.next();

        pr.quantity = qu2.value(0).toInt();

        listProducts.push_back(pr);
    }

    return listProducts;
}

QList <product> DatabaseModule::getListProductByIdInvoice(int idInvoice)
{
    QList <product> listProducts;
    product pr;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM product WHERE id = (SELECT idProduct FROM product_in_invoice WHERE idInvoice = :idInvoice)");
    qu.bindValue(":idInvoice", idInvoice);
    qu.exec();

    QSqlQuery qu2;
    qu2.prepare("SELECT price, quantity, accounting_price FROM product_in_invoice WHERE idProduct = :idProduct AND idInvoice = :idInvoice");
    qu2.bindValue(":idInvoice", idInvoice);

    while(qu.next())
    {
        pr.id = qu.value(0).toInt();
        pr.title = qu.value(1).toString();
        pr.measuring = qu.value(2).toString();
        pr.nomenclature = qu.value(3).toString();

        qu2.bindValue(":idProduct", pr.id);
        qu2.exec();
        qu2.next();

        pr.priceSender = qu2.value(0).toFloat();
        pr.quantity = qu2.value(1).toInt();
        pr.price = qu2.value(2).toFloat();

        listProducts.push_back(pr);
    }

    return listProducts;
}

storage DatabaseModule::getStorageById(int id)
{
    storage st;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM storage WHERE id = :id");
    qu.bindValue(":id", id);
    qu.exec();
    qu.next();

    st.id = qu.value(0).toInt();
    st.title = qu.value(1).toString();
    st.city = qu.value(2).toString();
    st.address = qu.value(3).toString();
    st.capacity = qu.value(4).toInt();
    st.listProducts = getListProductByIdStorage(st.id);

    return st;
}

client DatabaseModule::getClientById(int id)
{
    client cl;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM clients WHERE id = :id");
    qu.bindValue(":id", id);
    qu.exec();
    qu.next();

    cl.id = qu.value(0).toInt();
    cl.pib = qu.value(1).toString();
    cl.phonenumber = qu.value(2).toString();
    cl.title = qu.value(3).toString();

    return cl;
}

paymenttype DatabaseModule::getPaymentTypeById(int id)
{
    paymenttype pt;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM payment_type WHERE id = :id");
    qu.bindValue(":id", id);
    qu.exec();
    qu.next();

    pt.id = qu.value(0).toInt();
    pt.title = qu.value(1).toString();

    return pt;
}

QList <invoice> DatabaseModule::getListInvoiceByType(int idType)
{
    QList <invoice> listInvoices;
    invoice tmp_invoice;

    QSqlQuery query;
    query.prepare("SELECT * FROM invoices WHERE idTypeInvoice = :idTypeInvoice");
    query.bindValue(":idTypeInvoice", idType);
    query.exec();

    while(query.next())
    {
        tmp_invoice.id = query.value(0).toInt();
        tmp_invoice.sum = query.value(1).toFloat();
        tmp_invoice.data = query.value(2).toDate();
        tmp_invoice.typeInvoice = getTypeInvoiceById(query.value(3).toInt());
        tmp_invoice.listProducts = getListProductByIdInvoice(tmp_invoice.id);

        switch (tmp_invoice.typeInvoice.id)
        {
        case 1:
        {
            tmp_invoice.storageRecipient = getStorageById(query.value(5).toInt());
            tmp_invoice.provider = getProviderById(query.value(7).toInt());
            tmp_invoice.note = query.value(10).toString();
            tmp_invoice.storno = query.value(11).toInt();
            tmp_invoice.userRecipient = getUserById(query.value(12).toInt());
            break;
        }
        case 2:
        {
            tmp_invoice.storageSender = getStorageById(query.value(4).toInt());
            tmp_invoice.userSender = getUserById(query.value(6).toInt());
            tmp_invoice.client = getClientById(query.value(8).toInt());
            tmp_invoice.paymentType = getPaymentTypeById(query.value(9).toInt());
            tmp_invoice.note = query.value(10).toString();
            tmp_invoice.storno = query.value(11).toInt();
            break;
        }
        case 3:
        {
            tmp_invoice.storageSender = getStorageById(query.value(4).toInt());
            tmp_invoice.storageRecipient = getStorageById(query.value(5).toInt());
            tmp_invoice.userSender = getUserById(query.value(6).toInt());
            tmp_invoice.userRecipient = getUserById(query.value(12).toInt());
            tmp_invoice.note = query.value(10).toString();
            tmp_invoice.storno = query.value(11).toInt();
            break;
        }
        }

        listInvoices.push_back(tmp_invoice);
    }

    return listInvoices;
}

QList <invoice> DatabaseModule::getListInvoiceByType(int idType, int idStorage)
{
    QList <invoice> listInvoices;
    invoice tmp_invoice;

    QSqlQuery query;
    query.prepare("SELECT * FROM invoices WHERE idTypeInvoice = :idTypeInvoice AND (idStorageSender = :idStorage OR idStorageRecipient = :idStorage)");
    query.bindValue(":idTypeInvoice", idType);
    query.bindValue(":idStorage", idStorage);
    query.exec();

    while(query.next())
    {
        tmp_invoice.id = query.value(0).toInt();
        tmp_invoice.sum = query.value(1).toFloat();
        tmp_invoice.data = query.value(2).toDate();
        tmp_invoice.typeInvoice = getTypeInvoiceById(query.value(3).toInt());
        tmp_invoice.listProducts = getListProductByIdInvoice(tmp_invoice.id);

        switch (tmp_invoice.typeInvoice.id)
        {
        case 1:
        {
            tmp_invoice.storageRecipient = getStorageById(query.value(5).toInt());
            tmp_invoice.provider = getProviderById(query.value(7).toInt());
            tmp_invoice.note = query.value(10).toString();
            tmp_invoice.storno = query.value(11).toInt();
            tmp_invoice.userRecipient = getUserById(query.value(12).toInt());
            break;
        }
        case 2:
        {
            tmp_invoice.storageSender = getStorageById(query.value(4).toInt());
            tmp_invoice.userSender = getUserById(query.value(6).toInt());
            tmp_invoice.client = getClientById(query.value(8).toInt());
            tmp_invoice.paymentType = getPaymentTypeById(query.value(9).toInt());
            tmp_invoice.note = query.value(10).toString();
            tmp_invoice.storno = query.value(11).toInt();
            break;
        }
        case 3:
        {
            tmp_invoice.storageSender = getStorageById(query.value(4).toInt());
            tmp_invoice.storageRecipient = getStorageById(query.value(5).toInt());
            tmp_invoice.userSender = getUserById(query.value(6).toInt());
            tmp_invoice.userRecipient = getUserById(query.value(12).toInt());
            tmp_invoice.note = query.value(10).toString();
            tmp_invoice.storno = query.value(11).toInt();
            break;
        }
        }

        listInvoices.push_back(tmp_invoice);
    }

    return listInvoices;
}

QList <invoice> DatabaseModule::getListInvoiceByTypeAvialableConnectedUser(int idType)
{
    QList <invoice> listInvoices;

    for(int i = 0; i < connectedUser.listStorages.size(); i++)
        listInvoices += getListInvoiceByType(idType, connectedUser.listStorages.at(i).id);

    return listInvoices;
}

QList <product> DatabaseModule::getListProducts()
{
    QList <product> listProducts;
    product pr;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM product");
    qu.exec();

    while(qu.next())
    {
        pr.id = qu.value(0).toInt();
        pr.title = qu.value(1).toString();
        pr.measuring = qu.value(2).toString();
        pr.nomenclature = qu.value(3).toString();
        pr.price = qu.value(4).toFloat();
        listProducts.push_back(pr);
    }

    return listProducts;
}

QList <storage> DatabaseModule::getListStorages()
{
    QList <storage> listStorages;
    storage st;

    db.open();

    QSqlQuery qu;
    QSqlQuery qu2;

    for(int i = 0; i < connectedUser.listStorages.size(); i++)
    {
        qu.prepare("SELECT * FROM storage WHERE id = :idStorage");
        qu.bindValue(":idStorage", connectedUser.listStorages.at(i).id);
        //qu.prepare("SELECT * FROM storage");
        qu.exec();

        qu2.prepare("SELECT sum(quantity) FROM product_in_storage WHERE idStorage = :idStorage");

        while(qu.next())
        {
            st.id = qu.value(0).toInt();
            st.title = qu.value(1).toString();
            st.city = qu.value(2).toString();
            st.address = qu.value(3).toString();
            st.capacity = qu.value(4).toInt();

            qu2.bindValue(":idStorage", st.id);
            qu2.exec();
            qu2.next();

            st.workload = qu2.value(0).toInt();
            st.listProducts = getListProductByIdStorage(st.id);

            listStorages.push_back(st);
        }
    }

    return listStorages;
}

QList <position> DatabaseModule::getListPositions()
{
    QList <position> listPositions;
    position pos;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM position");
    qu.exec();

    while(qu.next())
    {
        pos.id = qu.value(0).toInt();
        pos.title = qu.value(1).toString();

        listPositions.push_back(pos);
    }

    return listPositions;
}

QList <user> DatabaseModule::getListUsers()
{
    QList <user> listUsers;
    user us;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM users");
    qu.exec();

    while(qu.next())
    {
        us.id = qu.value(0).toInt();
        us.login = qu.value(1).toString();
        us.password = qu.value(2).toString();
        us.pib = qu.value(3).toString();
        us.phonenumber = qu.value(4).toString();
        us.position = getPositionById(qu.value(5).toInt());

        QSqlQuery qu2;
        qu2.prepare("SELECT idStorage FROM user_storage WHERE idUser = :idUser");
        qu2.bindValue(":idUser", us.id);
        qu2.exec();

        while(qu2.next())
            us.listStorages.push_back(getStorageById(qu2.value(0).toInt()));

        listUsers.push_back(us);
    }

    return listUsers;
}

QList <client> DatabaseModule::getListClients()
{
    QList <client> listClients;
    client cl;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM clients");
    qu.exec();

    while(qu.next())
    {
        cl.id = qu.value(0).toInt();
        cl.pib = qu.value(1).toString();
        cl.phonenumber = qu.value(2).toString();
        cl.title = qu.value(3).toString();

        listClients.push_back(cl);
    }

    return listClients;
}

QList <provider> DatabaseModule::getListProviders()
{
    QList <provider> listProviders;
    provider pr;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM providers");
    qu.exec();

    while(qu.next())
    {
        pr.id = qu.value(0).toInt();
        pr.title = qu.value(1).toString();
        pr.pib = qu.value(2).toString();
        pr.phonenumber = qu.value(3).toString();
        pr.requisites = qu.value(4).toString();

        listProviders.push_back(pr);
    }

    return listProviders;
}

QList <user> DatabaseModule::getListUsersByPosition(int id_position)
{
    QList <user> listUsers;
    user us;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM users WHERE idPosition = :idPosition");
    qu.bindValue(":idPosition", id_position);
    qu.exec();

    while(qu.next())
    {
        us.id = qu.value(0).toInt();
        us.login = qu.value(1).toString();
        us.password = qu.value(2).toString();
        us.pib = qu.value(3).toString();
        us.phonenumber = qu.value(4).toString();
        us.position = getPositionById(qu.value(5).toInt());

        QSqlQuery qu2;
        qu2.prepare("SELECT idStorage FROM user_storage WHERE idUser = :idUser");
        qu2.bindValue(":idUser", us.id);
        qu2.exec();

        while(qu2.next())
            us.listStorages.push_back(getStorageById(qu2.value(0).toInt()));

        listUsers.push_back(us);
    }

    return listUsers;
}

int DatabaseModule::getNextIdInvoice()
{
    int number;

    QSqlQuery qu;
    qu.prepare("SELECT max(id) FROM invoices");
    qu.exec();
    qu.next();

    number = qu.value(0).toInt();

    return number;
}

QList <storno> DatabaseModule::getListStornedInvoicesAvialableSelectedUser()
{
    QList <storno> listStorno;
    storno st;
    QSqlQuery qu;
    qu.prepare("SELECT * FROM storno");
    qu.exec();

    while(qu.next())
    {
        st.invoice = getInvoiceById(qu.value(0).toInt());
        st.note = qu.value(1).toString();
        listStorno.push_back(st);
    }

    return listStorno;
}

invoice DatabaseModule::getInvoiceById(int id)
{
    invoice tmp_invoice;

    QSqlQuery query;
    query.prepare("SELECT * FROM invoices WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    query.next();

    tmp_invoice.id = query.value(0).toInt();
    tmp_invoice.sum = query.value(1).toFloat();
    tmp_invoice.data = query.value(2).toDate();
    tmp_invoice.typeInvoice = getTypeInvoiceById(query.value(3).toInt());
    tmp_invoice.listProducts = getListProductByIdInvoice(tmp_invoice.id);

    switch (tmp_invoice.typeInvoice.id)
    {
    case 1:
    {
        tmp_invoice.storageRecipient = getStorageById(query.value(5).toInt());
        tmp_invoice.provider = getProviderById(query.value(7).toInt());
        tmp_invoice.note = query.value(10).toString();
        tmp_invoice.storno = query.value(11).toInt();
        tmp_invoice.userRecipient = getUserById(query.value(12).toInt());
        break;
    }
    case 2:
    {
        tmp_invoice.storageSender = getStorageById(query.value(4).toInt());
        tmp_invoice.userSender = getUserById(query.value(6).toInt());
        tmp_invoice.client = getClientById(query.value(8).toInt());
        tmp_invoice.paymentType = getPaymentTypeById(query.value(9).toInt());
        tmp_invoice.note = query.value(10).toString();
        tmp_invoice.storno = query.value(11).toInt();
        break;
    }
    case 3:
    {
        tmp_invoice.storageSender = getStorageById(query.value(4).toInt());
        tmp_invoice.storageRecipient = getStorageById(query.value(5).toInt());
        tmp_invoice.userSender = getUserById(query.value(6).toInt());
        tmp_invoice.userRecipient = getUserById(query.value(12).toInt());
        tmp_invoice.note = query.value(10).toString();
        tmp_invoice.storno = query.value(11).toInt();
        break;
    }
    }

    return tmp_invoice;
}

product DatabaseModule::getProductById(int id)
{
    product pr;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM product WHERE id = :id");
    qu.bindValue(":id", id);
    qu.exec();

    while(qu.next())
    {
        pr.id = qu.value(0).toInt();
        pr.title = qu.value(1).toString();
        pr.measuring = qu.value(2).toString();
        pr.nomenclature = qu.value(3).toString();
        pr.price = qu.value(4).toFloat();
    }

    return pr;
}

resultQuery DatabaseModule::deleteClient(client client)
{
    resultQuery result;

    QSqlQuery qu;
    qu.prepare("SELECT id FROM invoices WHERE idClient = :id");
    qu.bindValue(":id", client.id);
    qu.exec();
    if(qu.size())
    {
        result.flag = false;
        result.message = "Клиент фигурирует в накладных, удаление не возможно.";
        return result;
    }

    qu.prepare("DELETE FROM clients WHERE id = :id");
    qu.bindValue(":id", client.id);
    qu.exec();

    result.flag = true;
    result.message = "Клиент удалён.";
    return result;
}

resultQuery DatabaseModule::deleteProvider(provider provider)
{
    resultQuery result;

    QSqlQuery qu;
    qu.prepare("SELECT id FROM invoices WHERE idProvider = :id");
    qu.bindValue(":id", provider.id);
    qu.exec();

    if(qu.size())
    {
        result.flag = false;
        result.message = "Поставщик фигурирует в накладных, удаление не возможно.";
        return result;
    }

    qu.prepare("DELETE FROM providers WHERE id = :id");
    qu.bindValue(":id", provider.id);
    qu.exec();

    result.flag = true;
    result.message = "Поставщик удалён.";
    return result;
}

resultQuery DatabaseModule::deleteUser(user user)
{
    resultQuery result;

    QSqlQuery qu;
    qu.prepare("SELECT id FROM invoices WHERE idUserSender = :id OR idUserRecipient = :id");
    qu.bindValue(":id", user.id);
    qu.exec();
    qu.next();
    qDebug() << user.id << qu.value(0).toInt();

    if(qu.size())
    {
        result.flag = false;
        result.message = "Пользователь фигурирует в накладных, удаление не возможно.";
        return result;
    }

    qu.prepare("DELETE FROM users WHERE id = :id");
    qu.bindValue(":id", user.id);
    qu.exec();

    qu.prepare("DELETE FROM user_storage WHERE idUser = :id");
    qu.bindValue(":id", user.id);
    qu.exec();

    result.flag = true;
    result.message = "Пользователь удалён.";
    return result;
}

resultQuery DatabaseModule::deleteStorage(storage storage)
{
    resultQuery result;

    QSqlQuery qu;
    qu.prepare("SELECT id FROM invoices WHERE idStorageSender = :id OR idStorageRecipient = :id");
    qu.bindValue(":id", storage.id);
    qu.exec();
    if(qu.size())
    {
        result.flag = false;
        result.message = "Склад фигурирует в накладных, удаление не возможно.";
        return result;
    }

    qu.prepare("DELETE FROM storage WHERE idStorage = :id");
    qu.bindValue(":id", storage.id);
    qu.exec();

    qu.prepare("DELETE FROM user_storage WHERE id = :id");
    qu.bindValue(":id", storage.id);
    qu.exec();

    result.flag = true;
    result.message = "Склад удалён.";
    return result;
}

resultQuery DatabaseModule::deleteProduct(product product)
{
    resultQuery result;

    QSqlQuery qu;
    qu.prepare("SELECT id FROM product_in_invoice WHERE idProduct = :id");
    qu.bindValue(":id", product.id);
    qu.exec();
    if(qu.size())
    {
        result.flag = false;
        result.message = "Товар фигурирует в накладных, удаление не возможно.";
        return result;
    }

    qu.prepare("DELETE FROM product WHERE id = :id");
    qu.bindValue(":id", product.id);
    qu.exec();

    qu.prepare("DELETE FROM storage WHERE id = :id");
    qu.bindValue(":id", product.id);
    qu.exec();

    result.flag = true;
    result.message = "Товар удалён.";
    return result;
}

resultQuery DatabaseModule::setClient(client client)
{
    resultQuery result;

    QSqlQuery query;
    query.prepare("UPDATE clients SET PIB = :PIB, phonenumber = :phonenumber, title = :title WHERE id = :id");
    query.bindValue(":id", client.id);
    query.bindValue(":PIB", QVariant(client.pib).toString());
    query.bindValue(":phonenumber", QVariant(client.phonenumber).toString());
    query.bindValue(":title", QVariant(client.title).toString());
    query.exec();

    result.flag = true;
    result.message = "Клиент изменён.";
    return result;
}

resultQuery DatabaseModule::setProvider(provider provider)
{
    resultQuery result;

    QSqlQuery query;

    query.prepare("UPDATE providers SET title = :title, PIB = :PIB, phonenumber = :phonenumber, requisites = :requisites WHERE id = :id");
    query.bindValue(":id", provider.id);
    query.bindValue(":title", QVariant(provider.title).toString());
    query.bindValue(":PIB", QVariant(provider.pib).toString());
    query.bindValue(":phonenumber", QVariant(provider.phonenumber).toString());
    query.bindValue(":requisites", QVariant(provider.requisites).toString());
    query.exec();

    result.flag = true;
    result.message = "Поставщик изменён.";
    return result;
}

resultQuery DatabaseModule::setProduct(product product)
{
    resultQuery result;

    QSqlQuery query;

    query.prepare("UPDATE product SET title = :title, measuring = :measuring, nomenclature = :nomenclature, price = :price WHERE id = :id");
    query.bindValue(":id", product.id);
    query.bindValue(":title", product.title);
    query.bindValue(":measuring", product.measuring);
    query.bindValue(":nomenclature", product.nomenclature);
    query.bindValue(":price", product.price);
    query.exec();

    result.flag = true;
    result.message = "Товар изменён.";
    return result;
}

resultQuery DatabaseModule::setStorage(storage storage)
{
    resultQuery result;

    QSqlQuery query;

    query.prepare("UPDATE storage SET title = :title, city = :city, address = :address, capacity = :capacity WHERE id = :id");
    query.bindValue(":id", storage.id);
    query.bindValue(":title", QVariant(storage.title).toString());
    query.bindValue(":city", QVariant(storage.city).toString());
    query.bindValue(":address", QVariant(storage.address).toString());
    query.bindValue(":capacity", storage.capacity);
    query.exec();

    result.flag = true;
    result.message = "Склад изменён.";
    return result;
}

resultQuery DatabaseModule::setUser(user user)
{
    resultQuery result;

    QSqlQuery query;

    query.prepare("UPDATE users SET login = :login, password = :password, PIB = :PIB, phonenumber = :phonenumber, idPosition = :idPosition WHERE id = :id");
    query.bindValue(":id", user.id);
    query.bindValue(":login", QVariant(user.login).toString());
    query.bindValue(":password", QVariant(user.password).toString());
    query.bindValue(":PIB", QVariant(user.pib).toString());
    query.bindValue(":phonenumber", QVariant(user.phonenumber).toString());
    query.bindValue(":idPosition", user.position.id);
    query.exec();

    if(user.listStorages.size() != 0)
    {
        query.prepare("DELETE FROM user_storage WHERE idUser = :id");
        query.bindValue(":id", user.id);
        query.exec();

        query.prepare("INSERT user_storage VALUES(:idUser, :idStorage)");

        for(int i = 0; i < user.listStorages.size(); i++)
        {
            query.bindValue(":idUser", user.id);
            query.bindValue(":idStorage", user.listStorages.at(i).id);
            query.exec();
        }
    }

    result.flag = true;
    result.message = "Пользователь изменён.";
    return result;
}

QList <invoice> DatabaseModule::getRepordByComingInvoices(QDate begin, QDate end)
{
    QList <invoice> listInvoices;
    invoice tmp_invoice;

    QSqlQuery query;
    query.prepare("SELECT * FROM invoices WHERE idTypeInvoice = :idTypeInvoice AND date >= :begin AND date <= :end");
    query.bindValue(":idTypeInvoice", 1);
    query.bindValue(":begin", begin);
    query.bindValue(":end", end);
    query.exec();

    while(query.next())
    {
        tmp_invoice.id = query.value(0).toInt();
        tmp_invoice.sum = query.value(1).toFloat();
        tmp_invoice.data = query.value(2).toDate();
        tmp_invoice.typeInvoice = getTypeInvoiceById(query.value(3).toInt());
        tmp_invoice.listProducts = getListProductByIdInvoice(tmp_invoice.id);

        tmp_invoice.storageRecipient = getStorageById(query.value(5).toInt());
        tmp_invoice.provider = getProviderById(query.value(7).toInt());
        tmp_invoice.note = query.value(10).toString();
        tmp_invoice.storno = query.value(11).toInt();
        tmp_invoice.userRecipient = getUserById(query.value(12).toInt());


        listInvoices.push_back(tmp_invoice);
    }

    return listInvoices;
}

QList <invoice> DatabaseModule::getRepordBySaleInvoices(QDate begin, QDate end)
{
    QList <invoice> listInvoices;
    invoice tmp_invoice;

    QSqlQuery query;
    query.prepare("SELECT * FROM invoices WHERE idTypeInvoice = :idTypeInvoice AND date >= :begin AND date <= :end");
    query.bindValue(":idTypeInvoice", 2);
    query.bindValue(":begin", begin);
    query.bindValue(":end", end);
    query.exec();

    while(query.next())
    {
        tmp_invoice.id = query.value(0).toInt();
        tmp_invoice.sum = query.value(1).toFloat();
        tmp_invoice.data = query.value(2).toDate();
        tmp_invoice.typeInvoice = getTypeInvoiceById(query.value(3).toInt());
        tmp_invoice.listProducts = getListProductByIdInvoice(tmp_invoice.id);

        tmp_invoice.storageSender = getStorageById(query.value(4).toInt());
        tmp_invoice.userSender = getUserById(query.value(6).toInt());
        tmp_invoice.client = getClientById(query.value(8).toInt());
        tmp_invoice.paymentType = getPaymentTypeById(query.value(9).toInt());
        tmp_invoice.note = query.value(10).toString();
        tmp_invoice.storno = query.value(11).toInt();

        listInvoices.push_back(tmp_invoice);
    }

    return listInvoices;
}

QList <product> DatabaseModule::getListProductByTypeInvoice(int type)
{
    QList <product> listProducts;
    QList <invoice> listInvoices = getListInvoiceByType(type);
    product pr;
    bool flag = true;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM product WHERE id = (SELECT idProduct FROM product_in_invoice WHERE idInvoice = :idInvoice)");
    for(int i = 0; i < listInvoices.size(); i++)
    {
        qu.bindValue(":idInvoice", listInvoices.at(i).id);
        qu.exec();

        while(qu.next())
        {
            pr.id = qu.value(0).toInt();
            for(int j = 0; j < listProducts.size(); j++)
                if(listProducts.at(j).id == pr.id)
                    flag = false;

            if(flag)
            {
                pr.title = qu.value(1).toString();
                pr.measuring = qu.value(2).toString();
                pr.nomenclature = qu.value(3).toString();

                listProducts.push_back(pr);
            }
        }
    }

    return listProducts;
}

QList <product> DatabaseModule::getReportByPopularProduct()
{
    QList <product> listProducts = getListProductByTypeInvoice(2);
    QList <invoice> listInvoices = getListInvoiceByType(2);

    QSqlQuery qu;
    qu.prepare("SELECT count(idProduct) FROM product_in_invoice WHERE idProduct = :idProduct AND idInvoice = :idInvoice");

    for(int j = 0; j < listInvoices.size(); j++)
    {
        for(int i = 0; i < listProducts.size(); i++)
        {
            qu.bindValue(":idProduct", listProducts.at(i).id);
            qu.bindValue(":idInvoice", listInvoices.at(j).id);
            qu.exec();
            qu.next();
            listProducts[i].quantity += qu.value(0).toInt();
        }
    }

    for(int i = 0; i < listProducts.size()-1; i++)
    {
        for(int j = 1; j < listProducts.size(); j++)
            if(listProducts.at(i).quantity < listProducts.at(j).quantity)
            {
                product tmp = listProducts[i];
                listProducts[i] = listProducts[j];
                listProducts[j] = tmp;
            }
    }

    return listProducts;
}

QList <invoice> DatabaseModule::getListInvoicesByTypeAndDate(int idType, QDate begin, QDate end)
{
    QList <invoice> listInvoices;
    invoice tmp_invoice;

    QSqlQuery query;
    query.prepare("SELECT * FROM invoices WHERE idTypeInvoice = :idTypeInvoice AND date >= :begin AND date <= :end");
    query.bindValue(":idTypeInvoice", idType);
    query.bindValue(":begin", begin);
    query.bindValue(":end", end);
    query.exec();

    while(query.next())
    {
        tmp_invoice.id = query.value(0).toInt();
        tmp_invoice.sum = query.value(1).toFloat();
        tmp_invoice.data = query.value(2).toDate();
        tmp_invoice.typeInvoice = getTypeInvoiceById(query.value(3).toInt());
        tmp_invoice.listProducts = getListProductByIdInvoice(tmp_invoice.id);

        switch (tmp_invoice.typeInvoice.id)
        {
        case 1:
        {
            tmp_invoice.storageRecipient = getStorageById(query.value(5).toInt());
            tmp_invoice.provider = getProviderById(query.value(7).toInt());
            tmp_invoice.note = query.value(10).toString();
            tmp_invoice.storno = query.value(11).toInt();
            tmp_invoice.userRecipient = getUserById(query.value(12).toInt());
            break;
        }
        case 2:
        {
            tmp_invoice.storageSender = getStorageById(query.value(4).toInt());
            tmp_invoice.userSender = getUserById(query.value(6).toInt());
            tmp_invoice.client = getClientById(query.value(8).toInt());
            tmp_invoice.paymentType = getPaymentTypeById(query.value(9).toInt());
            tmp_invoice.note = query.value(10).toString();
            tmp_invoice.storno = query.value(11).toInt();
            break;
        }
        case 3:
        {
            tmp_invoice.storageSender = getStorageById(query.value(4).toInt());
            tmp_invoice.storageRecipient = getStorageById(query.value(5).toInt());
            tmp_invoice.userSender = getUserById(query.value(6).toInt());
            tmp_invoice.userRecipient = getUserById(query.value(12).toInt());
            tmp_invoice.note = query.value(10).toString();
            tmp_invoice.storno = query.value(11).toInt();
            break;
        }
        }

        listInvoices.push_back(tmp_invoice);
    }

    return listInvoices;
}

QList <product> DatabaseModule::getReportBySaleProduct(QDate begin, QDate end)
{
    QList <product> listProducts;
    QList <invoice> listInvoices = getListInvoicesByTypeAndDate(2, begin, end);
    product pr;
    bool flag = true;

    QSqlQuery qu;
    qu.prepare("SELECT * FROM product WHERE id = (SELECT idProduct FROM product_in_invoice WHERE idInvoice = :idInvoice)");
    for(int i = 0; i < listInvoices.size(); i++)
    {
        qu.bindValue(":idInvoice", listInvoices.at(i).id);
        qu.exec();

        while(qu.next())
        {
            pr.id = qu.value(0).toInt();
            for(int j = 0; j < listProducts.size(); j++)
                if(listProducts.at(j).id == pr.id)
                    flag = false;

            if(flag)
            {
                pr.title = qu.value(1).toString();
                pr.measuring = qu.value(2).toString();
                pr.nomenclature = qu.value(3).toString();

                listProducts.push_back(pr);
            }
        }
    }

    qu.prepare("SELECT price, quantity, accounting_price FROM product_in_invoice WHERE idInvoice = :idInvoice AND idProduct = :idProduct");
    for(int i = 0; i < listInvoices.size(); i++)
    {
        qu.bindValue(":idInvoice", listInvoices.at(i).id);
        for(int j = 0; j < listProducts.size(); j++)
        {
            qu.bindValue(":idProduct", listProducts.at(j).id);
            qu.exec();
            qu.next();

            if(qu.value(0).toFloat() != 0 && qu.value(1).toFloat() != 0)
            {
                listProducts[j].priceSender = getPriceComingByIdProduct(listProducts.at(j).id);
                listProducts[j].quantity += qu.value(1).toInt();
                listProducts[j].price = qu.value(0).toFloat();
            }
        }
    }

    return listProducts;
}

float DatabaseModule::getPriceComingByIdProduct(int id)
{
    float price;
    QList <invoice> listInvoices = getListInvoiceByType(1);

    QSqlQuery qu;
    qu.prepare("SELECT price FROM product_in_invoice WHERE idProduct = :idProduct AND idInvoice = :idInvoice");
    qu.bindValue(":idProduct", id);
    for(int i = 0; i < listInvoices.size(); i++)
    {
        qu.bindValue(":idInvoice", listInvoices.at(i).id);
        qu.exec();
        if(qu.size())
        {
            qu.next();
            price = qu.value(0).toFloat();
        }
    }
    return price;
}

resultQuery DatabaseModule::addStorno(storno storno)
{
    resultQuery result;

    QSqlQuery query;
    query.prepare("SELECT note FROM storno WHERE idInvice = :idInvoice");
    query.bindValue(":idInvoice", storno.invoice.id);
    query.exec();
    query.next();

    if(query.size())
    {
        result.message = "Эта накладная уже сторнирована.";
        result.flag = false;
        return result;
    }
    else
    {
        query.prepare("INSERT INTO storno (idInvice, note) VALUES(:idInvoice, :note)");
        query.bindValue(":idInvoice", storno.invoice.id);
        query.bindValue(":note", storno.note);
        query.exec();

        query.prepare("UPDATE FROM invoices SET storno = 1 WHERE id = :idInvoice");
        query.bindValue("idInvoice", storno.invoice.id);
        query.exec();

        result.flag = true;
        result.message = "Сторнировано.";
        return result;
    }
}
