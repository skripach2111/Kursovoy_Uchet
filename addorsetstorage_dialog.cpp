#include "addorsetstorage_dialog.h"
#include "ui_addorsetstorage_dialog.h"

AddOrSetStorage_Dialog::AddOrSetStorage_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetStorage_Dialog)
{
    ui->setupUi(this);
}

AddOrSetStorage_Dialog::~AddOrSetStorage_Dialog()
{
    delete ui;
}
