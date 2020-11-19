#include "addorsetuser_dialog.h"
#include "ui_addorsetuser_dialog.h"

AddOrSetUser_Dialog::AddOrSetUser_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetUser_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Save, SIGNAL(clicked()), this, SLOT(slot_pushButton_Save_clicked()));
    connect(ui->pushButton_ToSelected, SIGNAL(clicked()), this, SLOT(slot_pushButton_ToSelected_clicked()));
    connect(ui->pushButton_ToAvialable, SIGNAL(clicked()), this, SLOT(slot_pushButton_ToAvialable_clicked()));
}

AddOrSetUser_Dialog::~AddOrSetUser_Dialog()
{
    delete ui;
}

void AddOrSetUser_Dialog::setUser(user user)
{
    us = user;

    ui->lineEdit_Login->setText(us.login);
    ui->lineEdit_PIB->setText(us.pib);
    ui->lineEdit_Password->setText(us.password);
    ui->lineEdit_PhoneNumber->setText(us.phonenumber);
    ui->comboBox_Position->setCurrentText(us.position.title);
    //setCurrentPosition(us.position.id);

    updateTableAvialable();
    updateTableSelected();
}

void AddOrSetUser_Dialog::updatePosition()
{
    QList <position> listPosition = db.getListPositions();

    ui->comboBox_Position->clear();

    for(int i = 0; i < listPosition.size(); i++)
        ui->comboBox_Position->addItem(listPosition.at(i).title);
}

void AddOrSetUser_Dialog::setCurrentPosition(int id)
{
    QList <position> listPositions = db.getListPositions();

    for(int i = 0; i < listPositions.size(); i++)
        if(id == listPositions.at(i).id)
            ui->comboBox_Position->setCurrentIndex(i);
}

void AddOrSetUser_Dialog::setConnection(DatabaseModule db_connection)
{
    db = db_connection;

    updatePosition();
    updateTableAvialable();
}

void AddOrSetUser_Dialog::updateTableAvialable()
{
    QList <storage> listStorage = db.getListStorages();

    bool flag = true;

    ui->listWidget_AvialableStorage->clear();

    for(int i = 0; i < listStorage.size(); i++)
    {
        for(int j = 0; j < us.listStorages.size(); j++)
            if(listStorage.at(i).id == us.listStorages.at(j).id)
                flag = false;

        if(flag)
            ui->listWidget_AvialableStorage->addItem(listStorage.at(i).title);

        flag = true;
    }
}

void AddOrSetUser_Dialog::updateTableSelected()
{
    ui->listWidget_SelectedStorage->clear();

    for(int i = 0; i < us.listStorages.size(); i++)
        ui->listWidget_SelectedStorage->addItem(us.listStorages.at(i).title);
}

void AddOrSetUser_Dialog::slot_pushButton_ToSelected_clicked()
{
    QList <storage> listStorage = db.getListStorages();

    for(int i = 0; i < listStorage.size(); i++)
        if(ui->listWidget_AvialableStorage->currentItem()->text() == listStorage.at(i).title)
            us.listStorages.push_back(listStorage.at(i));

    updateTableAvialable();
    updateTableSelected();
}

void AddOrSetUser_Dialog::slot_pushButton_ToAvialable_clicked()
{
    for(int i = 0; i < us.listStorages.size(); i++)
        if(ui->listWidget_SelectedStorage->currentItem()->text() == us.listStorages.at(i).title)
            us.listStorages.removeAt(i);

    updateTableAvialable();
    updateTableSelected();
}

void AddOrSetUser_Dialog::slot_pushButton_Save_clicked()
{
    us.login = "";
    us.password = "";
    us.phonenumber = "";
    us.pib = "";

    us.login = ui->lineEdit_Login->text();
    us.password = ui->lineEdit_Password->text();
    us.phonenumber = ui->lineEdit_PhoneNumber->text();
    us.pib = ui->lineEdit_PIB->text();

    QList <position> listPosition = db.getListPositions();
    for(int i = 0; i < listPosition.size(); i++)
        if(ui->comboBox_Position->currentText() == listPosition.at(i).title)
            us.position = listPosition.at(i);

    if(us.login.size() != 0 && us.password.size() != 0 && us.phonenumber.size() != 0 && us.pib.size() != 0)
        this->close();
}

user AddOrSetUser_Dialog::getUser()
{
    return us;
}
