#include "addorsetproductininvoice_dialog.h"
#include "ui_addorsetproductininvoice_dialog.h"

AddOrSetProductInInvoice_Dialog::AddOrSetProductInInvoice_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetProductInInvoice_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_ChooseProduct, SIGNAL(clicked()), this, SLOT(slot_pushButton_ChooseProduct_clicked()));
    connect(ui->pushButton_Enter, SIGNAL(clicked()), this, SLOT(slot_pushButton_Enter_clicked()));
    connect(ui->spinBox_NumberUnits, SIGNAL(editingFinished()), this, SLOT(slot_spinBox_NumberUnits_editingFinished()));
    connect(ui->doubleSpinBox_PriceUnitsPurchase, SIGNAL(editingFinished()), this, SLOT(slot_doubleSpinBox_PriceUnitsPurchase_editingFinished()));
}

AddOrSetProductInInvoice_Dialog::~AddOrSetProductInInvoice_Dialog()
{
    delete ui;
}

void AddOrSetProductInInvoice_Dialog::setProduct(product product)
{
    pr = product;

    ui->label_Name->setText(pr.title);
    ui->label_Measuring->setText(pr.measuring);
    ui->label_Nomenclature->setText(pr.nomenclature);
    ui->label_PriceUnit->setText(QVariant(pr.price).toString());
    ui->spinBox_NumberUnits->setValue(pr.quantity);
    ui->doubleSpinBox_PriceUnitsPurchase->setValue(pr.priceSender);

    updateSum();
}

void AddOrSetProductInInvoice_Dialog::updateSum()
{
    ui->label_SumPurchase->setText(QVariant(ui->spinBox_NumberUnits->value()*ui->doubleSpinBox_PriceUnitsPurchase->value()).toString());
    ui->label_SumSale->setText(QVariant(ui->spinBox_NumberUnits->value()*pr.price).toString());
}

void AddOrSetProductInInvoice_Dialog::slot_spinBox_NumberUnits_editingFinished()
{
    updateSum();
}

void AddOrSetProductInInvoice_Dialog::slot_doubleSpinBox_PriceUnitsPurchase_editingFinished()
{
    updateSum();
}

void AddOrSetProductInInvoice_Dialog::slot_pushButton_ChooseProduct_clicked()
{
    ChooseProduct_Dialog ChooseDialog;
    ChooseDialog.setDialog(db);
    ChooseDialog.exec();

    if(ChooseDialog.getSelectedProduct().id != 0)
    {
        pr = ChooseDialog.getSelectedProduct();

        ui->label_Name->setText(pr.title);
        ui->label_Measuring->setText(pr.measuring);
        ui->label_Nomenclature->setText(pr.nomenclature);
        ui->label_PriceUnit->setText(QVariant(pr.price).toString());

        updateSum();
    }
}

void AddOrSetProductInInvoice_Dialog::slot_pushButton_Enter_clicked()
{
    pr.priceSender = ui->doubleSpinBox_PriceUnitsPurchase->value();
    pr.quantity = ui->spinBox_NumberUnits->value();

    if(pr.quantity != 0)
        this->close();
}

product AddOrSetProductInInvoice_Dialog::getProduct()
{
    return pr;
}

void AddOrSetProductInInvoice_Dialog::setConnection(DatabaseModule db_connection)
{
    db = db_connection;
}
