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

void MoreAboutInvoice_Dialog::setDialog(invoice invoice)
{
    inv = invoice;

    ui->label_NumberInvoice->setText(ui->label_NumberInvoice->text()+" "+QVariant(inv.id).toString());
    ui->label_TypeInvoice->setText(inv.typeInvoice.title);
    ui->label_TypePayment->setText(inv.paymentType.title);
    ui->label_SumPayment->setText(QVariant(inv.sum).toString());
    ui->label_Date->setText(inv.data.toString(Qt::LocalDate));

    switch (inv.typeInvoice.id)
    {
    case 1:
    {
        ui->label_NameSender->setText(inv.provider.title);
        ui->label_NameRecipient->setText(inv.userRecipient.pib);
        ui->label_NameStorageRecipient->setText(inv.storageRecipient.title);
        break;
    }
    case 2:
    {
        ui->label_NameSender->setText(inv.userSender.pib);
        ui->label_NameRecipient->setText(inv.client.title);
        ui->label_labelNameStorageSender->setText(inv.storageSender.title);
        break;
    }
    case 3:
    {
        ui->label_NameSender->setText(inv.userSender.pib);
        ui->label_NameRecipient->setText(inv.userRecipient.pib);
        ui->label_NameStorageRecipient->setText(inv.storageRecipient.title);
        ui->label_labelNameStorageSender->setText(inv.storageSender.title);
        break;
    }
    }

    for(int i = 0; i < inv.listProducts.size(); i++)
    {
        ui->tableWidget_Products->insertRow(ui->tableWidget_Products->rowCount());
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 0, new QTableWidgetItem(inv.listProducts.at(i).nomenclature));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 1, new QTableWidgetItem(inv.listProducts.at(i).title));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 2, new QTableWidgetItem(inv.listProducts.at(i).measuring));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 3, new QTableWidgetItem(QVariant(inv.listProducts.at(i).quantity).toString()));
    }
}
