#include "addorsetuser_dialog.h"
#include "ui_addorsetuser_dialog.h"

AddOrSetUser_Dialog::AddOrSetUser_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetUser_Dialog)
{
    ui->setupUi(this);
}

AddOrSetUser_Dialog::~AddOrSetUser_Dialog()
{
    delete ui;
}
