#include "addorsetproductininvoice_dialog.h"
#include "ui_addorsetproductininvoice_dialog.h"

AddOrSetProductInInvoice_Dialog::AddOrSetProductInInvoice_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetProductInInvoice_Dialog)
{
    ui->setupUi(this);
}

AddOrSetProductInInvoice_Dialog::~AddOrSetProductInInvoice_Dialog()
{
    delete ui;
}
