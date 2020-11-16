#include "addorsetproduct_dialog.h"
#include "ui_addorsetproduct_dialog.h"

AddOrSetProduct_Dialog::AddOrSetProduct_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetProduct_Dialog)
{
    ui->setupUi(this);
}

AddOrSetProduct_Dialog::~AddOrSetProduct_Dialog()
{
    delete ui;
}
