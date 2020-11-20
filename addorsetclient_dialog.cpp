#include "addorsetclient_dialog.h"
#include "ui_addorsetclient_dialog.h"

AddOrSetClient_Dialog::AddOrSetClient_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetClient_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Save, SIGNAL(clicked()), this, SLOT(slot_pushButton_Save_clicked()));
}

AddOrSetClient_Dialog::~AddOrSetClient_Dialog()
{
    delete ui;
}

void AddOrSetClient_Dialog::setClient(client client)
{
    cl = client;

    ui->lineEdit_Name->setText(cl.title);
    ui->lineEdit_PIB->setText(cl.pib);
    ui->lineEdit_PhoneNumber->setText(cl.phonenumber);
}

client AddOrSetClient_Dialog::getClient()
{
    return cl;
}

void AddOrSetClient_Dialog::slot_pushButton_Save_clicked()
{
    cl.phonenumber = "";
    cl.pib = "";
    cl.title = "";

    cl.phonenumber = ui->lineEdit_PhoneNumber->text();
    cl.pib = ui->lineEdit_PIB->text();
    cl.title = ui->lineEdit_Name->text();

    if(cl.phonenumber.size() != 0 && cl.pib.size() != 0 && cl.title.size() != 0)
        this->close();
}
