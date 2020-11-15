#include "addinvoice_dialog.h"
#include "ui_addinvoice_dialog.h"

AddInvoice_Dialog::AddInvoice_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddInvoice_Dialog)
{
    ui->setupUi(this);
}

AddInvoice_Dialog::~AddInvoice_Dialog()
{
    delete ui;
}
