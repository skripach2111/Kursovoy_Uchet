#include "chooseclient_dialog.h"
#include "ui_chooseclient_dialog.h"

ChooseClient_Dialog::ChooseClient_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseClient_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Select, SIGNAL(clicked()), this, SLOT(slot_pushButton_Select_clicked()));
    connect(ui->lineEdit_Title, SIGNAL(textEdited(QString)), this, SLOT(slot_lineEdit_Title_textEdited()));
}

ChooseClient_Dialog::~ChooseClient_Dialog()
{
    delete ui;
}

void ChooseClient_Dialog::setDialog(DatabaseModule db_connection)
{
    db = db_connection;
    updateTable(db.getListClients());
}

void ChooseClient_Dialog::updateTable(QList<client> listClients)
{
    ui->listWidget_Clients->clear();

    for(int i = 0; i < listClients.size(); i++)
        ui->listWidget_Clients->addItem(listClients.at(i).title);
}

void ChooseClient_Dialog::searchingClient()
{
    QList <client> listClients = db.getListClients();
    QList <client> listClientsSearch;

    for(int i = 0; i < listClients.size(); i++)
        if(listClients.at(i).title.indexOf(ui->lineEdit_Title->text()) > -1)
            listClientsSearch.push_back(listClients.at(i));

    updateTable(listClientsSearch);
}

void ChooseClient_Dialog::slot_lineEdit_Title_textEdited()
{
    searchingClient();
}

void ChooseClient_Dialog::slot_pushButton_Select_clicked()
{
    QList <client> listClients = db.getListClients();

    for(int i = 0; i < listClients.size(); i++)
        if(listClients.at(i).title == ui->listWidget_Clients->currentItem()->text())
        {
            cl = listClients.at(i);
            i = listClients.size();
        }

    this->close();
}

client ChooseClient_Dialog::getSelectedClient()
{
    return cl;
}
