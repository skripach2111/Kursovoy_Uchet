#include "addorsetproduct_dialog.h"
#include "ui_addorsetproduct_dialog.h"

AddOrSetProduct_Dialog::AddOrSetProduct_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetProduct_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Save, SIGNAL(clicked()), this, SLOT(slot_pushButton_Save_clicked()));
}

AddOrSetProduct_Dialog::~AddOrSetProduct_Dialog()
{
    delete ui;
}

void AddOrSetProduct_Dialog::setProduct(product product)
{
    pr = product;

    ui->lineEdit_Name->setText(pr.title);
    ui->lineEdit_Nomenclature->setText(pr.nomenclature);
    ui->lineEdit_Measuring->setText(pr.measuring);
    ui->doubleSpinBox_Price->setValue(pr.price);
}

product AddOrSetProduct_Dialog::getProduct()
{
    return pr;
}

void AddOrSetProduct_Dialog::slot_pushButton_Save_clicked()
{
    pr.title = "";
    pr.nomenclature = "";
    pr.measuring = "";
    pr.price = 0;

    pr.title = ui->lineEdit_Name->text();
    pr.nomenclature = ui->lineEdit_Nomenclature->text();
    pr.measuring = ui->lineEdit_Measuring->text();
    pr.price = ui->doubleSpinBox_Price->value();

    if(pr.title.size() != 0 && pr.nomenclature.size() != 0 && pr.measuring.size() != 0 && pr.price != 0)
        this->close();
}
