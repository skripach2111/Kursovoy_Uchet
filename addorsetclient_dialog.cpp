#include "addorsetclient_dialog.h"
#include "ui_addorsetclient_dialog.h"

AddOrSetClient_Dialog::AddOrSetClient_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetClient_Dialog)
{
    ui->setupUi(this);
}

AddOrSetClient_Dialog::~AddOrSetClient_Dialog()
{
    delete ui;
}
