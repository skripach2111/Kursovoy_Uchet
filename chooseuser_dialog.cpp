#include "chooseuser_dialog.h"
#include "ui_chooseuser_dialog.h"

ChooseUser_Dialog::ChooseUser_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseUser_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Select, SIGNAL(clicked()), this, SLOT(slot_pushButton_Select_clicked()));
    connect(ui->lineEdit_PIB, SIGNAL(textEdited(QString)), this, SLOT(slot_lineEdit_PIB_textEdited()));
}

ChooseUser_Dialog::~ChooseUser_Dialog()
{
    delete ui;
}

void ChooseUser_Dialog::setDialog(DatabaseModule db_connection)
{
    db = db_connection;
    updateTable(db.getListUsersByPosition(4));
}

void ChooseUser_Dialog::updateTable(QList<user> listUsers)
{
    ui->listWidget_Users->clear();

    for(int i = 0; i < listUsers.size(); i++)
        ui->listWidget_Users->addItem(listUsers.at(i).pib);
}

void ChooseUser_Dialog::searchingUser()
{
    QList <user> listUsers = db.getListUsersByPosition(4);
    QList <user> listUsersSearch;

    for(int i = 0; i < listUsers.size(); i++)
        if(listUsers.at(i).pib.indexOf(ui->lineEdit_PIB->text()) > -1)
            listUsersSearch.push_back(listUsers.at(i));

    updateTable(listUsersSearch);
}

void ChooseUser_Dialog::slot_lineEdit_PIB_textEdited()
{
    searchingUser();
}

void ChooseUser_Dialog::slot_pushButton_Select_clicked()
{
    QList <user> listUsers = db.getListUsers();

    for(int i = 0; i < listUsers.size(); i++)
        if(listUsers.at(i).pib == ui->listWidget_Users->currentItem()->text())
        {
            us = listUsers.at(i);
            i = listUsers.size();
        }

    this->close();
}

user ChooseUser_Dialog::getSelectedUser()
{
    return us;
}
