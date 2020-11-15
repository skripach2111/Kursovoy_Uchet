#include "moreaboutinvoice_dialog.h"
#include "ui_moreaboutinvoice_dialog.h"

MoreAboutInvoice_Dialog::MoreAboutInvoice_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoreAboutInvoice_Dialog)
{
    ui->setupUi(this);
}

MoreAboutInvoice_Dialog::~MoreAboutInvoice_Dialog()
{
    delete ui;
}
