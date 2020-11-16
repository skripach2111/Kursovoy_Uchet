#include "addorsetprovider_dialog.h"
#include "ui_addorsetprovider_dialog.h"

AddOrSetProvider_Dialog::AddOrSetProvider_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetProvider_Dialog)
{
    ui->setupUi(this);
}

AddOrSetProvider_Dialog::~AddOrSetProvider_Dialog()
{
    delete ui;
}
