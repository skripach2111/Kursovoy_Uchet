#include "chooseproduct_dialog.h"
#include "ui_chooseproduct_dialog.h"

ChooseProduct_Dialog::ChooseProduct_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseProduct_Dialog)
{
    ui->setupUi(this);
}

ChooseProduct_Dialog::~ChooseProduct_Dialog()
{
    delete ui;
}
