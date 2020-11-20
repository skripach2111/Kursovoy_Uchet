#include "addorsetprovider_dialog.h"
#include "ui_addorsetprovider_dialog.h"

AddOrSetProvider_Dialog::AddOrSetProvider_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetProvider_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Save, SIGNAL(clicked()), this, SLOT(slot_pushButton_Save_clicked()));
}

AddOrSetProvider_Dialog::~AddOrSetProvider_Dialog()
{
    delete ui;
}

void AddOrSetProvider_Dialog::setProvider(provider provider)
{
    pr = provider;

    ui->lineEdit_Name->setText(pr.title);
    ui->lineEdit_PIB->setText(pr.pib);
    ui->lineEdit_PhoneNumber->setText(pr.phonenumber);
    ui->lineEdit_Requisites->setText(pr.requisites);
}

provider AddOrSetProvider_Dialog::getProvider()
{
    return pr;
}

void AddOrSetProvider_Dialog::slot_pushButton_Save_clicked()
{
    pr.phonenumber = "";
    pr.pib = "";
    pr.requisites = "";
    pr.title = "";

    pr.phonenumber = ui->lineEdit_PhoneNumber->text();
    pr.pib = ui->lineEdit_PIB->text();
    pr.requisites = ui->lineEdit_Requisites->text();
    pr.title = ui->lineEdit_Name->text();

    if(pr.phonenumber.size() != 0 && pr.pib.size() != 0 && pr.requisites.size() != 0 && pr.title.size() != 0)
        this->close();
}
