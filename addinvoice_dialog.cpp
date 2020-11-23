#include "addinvoice_dialog.h"
#include "ui_addinvoice_dialog.h"

AddInvoice_Dialog::AddInvoice_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddInvoice_Dialog)
{
    ui->setupUi(this);

    connect(ui->comboBox_TypeInvoice, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_comboBox_TypePayment_currentIndexChanged(int)));
    connect(ui->pushButton_AddProduct, SIGNAL(clicked()), this, SLOT(slot_pushButton_AddProduct_clicked()));
    connect(ui->pushButton_SetProduct, SIGNAL(clicked()), this, SLOT(slot_pushButton_SetProduct_clicked()));
    connect(ui->pushButton_DeleteProduct, SIGNAL(clicked()), this, SLOT(slot_pushButton_DeleteProduct_clicked()));
    connect(ui->pushButton_SetRecipient, SIGNAL(clicked()), this, SLOT(slot_pushButton_SetRecipient_clicked()));
    connect(ui->pushButton_SetSender, SIGNAL(clicked()), this, SLOT(slot_pushButton_SetSender_clicked()));
    connect(ui->pushButton_SetStorageRecipient, SIGNAL(clicked()), this, SLOT(slot_pushButton_SetStorageRecipient_clicked()));
    connect(ui->pushButton_SetStorageSender, SIGNAL(clicked()), this, SLOT(slot_pushButton_SetStorageSender_clicked()));
    connect(ui->pushButton_ClearRecipient, SIGNAL(clicked()), this, SLOT(slot_pushButton_ClearRecipient_clicked()));
    connect(ui->pushButton_ClearSender, SIGNAL(clicked()), this, SLOT(slot_pushButton_ClearSender_clicked()));
    connect(ui->pushButton_ClearStorageRecipient, SIGNAL(clicked()), this, SLOT(slot_pushButton_ClearStorageRecipient_clicked()));
    connect(ui->pushButton_ClearStorageSender, SIGNAL(clicked()), this, SLOT(slot_pushButton_ClearStorageSender_clicked()));
    connect(ui->pushButton_Save, SIGNAL(clicked()), this, (SLOT(slot_pushButton_Save_clicked())));
}

AddInvoice_Dialog::~AddInvoice_Dialog()
{
    delete ui;
}

void AddInvoice_Dialog::setDialog(DatabaseModule db_connection)
{
    db = db_connection;
    ui->comboBox_TypeInvoice->setCurrentIndex(0);
    ui->label_Date->setText(QDate::currentDate().toString(Qt::LocalDate));
    ui->label_NumberInvoice->setText(ui->label_NumberInvoice->text()+" "+QVariant(db.getNextIdInvoice()).toString());
}

void AddInvoice_Dialog::slot_comboBox_TypePayment_currentIndexChanged(int index)
{
    switch(ui->comboBox_TypeInvoice->currentIndex())
    {
    case 0:
    {
        ui->frame_Recipient->setVisible(true);
        ui->frame_Sender->setVisible(true);
        ui->frame_StorageRecipient->setVisible(true);
        ui->frame_StorageSender->setVisible(false);
        break;
    }
    case 1:
    {
        ui->frame_Recipient->setVisible(true);
        ui->frame_Sender->setVisible(true);
        ui->frame_StorageRecipient->setVisible(false);
        ui->frame_StorageSender->setVisible(true);
        break;
    }
    case 2:
    {
        ui->frame_Recipient->setVisible(true);
        ui->frame_Sender->setVisible(true);
        ui->frame_StorageRecipient->setVisible(true);
        ui->frame_StorageSender->setVisible(true);
        break;
    }
    }
}

void AddInvoice_Dialog::updateTypeInvoice()
{

}

void AddInvoice_Dialog::slot_pushButton_SetSender_clicked()
{
    switch (ui->comboBox_TypeInvoice->currentIndex())
    {
    case 0:
    {
        ChooseProvider_Dialog ChooseDialog;
        ChooseDialog.setDialog(db);
        ChooseDialog.exec();
        if(ChooseDialog.getSelectedProvider().id != 0)
        {
            inv.provider = ChooseDialog.getSelectedProvider();
            ui->label_NameSender->setText(inv.provider.title);
        }
        break;
    }
    case 1:
    {
        ChooseUser_Dialog ChooseDialog;
        ChooseDialog.setDialog(db);
        ChooseDialog.exec();
        if(ChooseDialog.getSelectedUser().id != 0)
        {
            inv.userSender = ChooseDialog.getSelectedUser();
            ui->label_NameSender->setText(inv.userSender.pib);
        }
        break;
    }
    case 2:
    {
        ChooseUser_Dialog ChooseDialog;
        ChooseDialog.setDialog(db);
        ChooseDialog.exec();
        if(ChooseDialog.getSelectedUser().id != 0)
        {
            inv.userSender = ChooseDialog.getSelectedUser();
            ui->label_NameSender->setText(inv.userSender.pib);
        }
        break;
    }
    }
}

void AddInvoice_Dialog::slot_pushButton_ClearSender_clicked()
{
    inv.provider.id = 0;
    inv.userSender.id = 0;
    ui->label_NameSender->setText("не задано");
}

void AddInvoice_Dialog::slot_pushButton_SetRecipient_clicked()
{
    switch (ui->comboBox_TypeInvoice->currentIndex())
    {
    case 0:
    {
        ChooseUser_Dialog ChooseDialog;
        ChooseDialog.setDialog(db);
        ChooseDialog.exec();
        if(ChooseDialog.getSelectedUser().id != 0)
        {
            inv.userRecipient = ChooseDialog.getSelectedUser();
            ui->label_NameRecipient->setText(inv.userRecipient.pib);
        }
        break;
    }
    case 1:
    {
        ChooseClient_Dialog ChooseDialog;
        ChooseDialog.setDialog(db);
        ChooseDialog.exec();
        if(ChooseDialog.getSelectedClient().id != 0)
        {
            inv.client = ChooseDialog.getSelectedClient();
            ui->label_NameRecipient->setText(inv.client.title);
        }
        break;
    }
    case 2:
    {
        ChooseUser_Dialog ChooseDialog;
        ChooseDialog.setDialog(db);
        ChooseDialog.exec();
        if(ChooseDialog.getSelectedUser().id != 0)
        {
            inv.userRecipient = ChooseDialog.getSelectedUser();
            ui->label_NameRecipient->setText(inv.userRecipient.pib);
        }
        break;
    }
    }
}

void AddInvoice_Dialog::slot_pushButton_ClearRecipient_clicked()
{
    inv.client.id = 0;
    inv.userRecipient.id = 0;
    ui->label_NameRecipient->setText("не задано");
}

void AddInvoice_Dialog::slot_pushButton_SetStorageSender_clicked()
{
    ChooseStorage_Dialog ChooseDialog;
    ChooseDialog.setDialog(db);
    ChooseDialog.exec();

    if(ChooseDialog.getSelectedStorage().id != 0)
    {
        inv.storageSender = ChooseDialog.getSelectedStorage();
        ui->label_StorageSender->setText(inv.storageSender.title);
    }
}

void AddInvoice_Dialog::slot_pushButton_ClearStorageSender_clicked()
{
    inv.storageSender.id = 0;
    ui->label_StorageSender->setText("не задано");
}

void AddInvoice_Dialog::slot_pushButton_SetStorageRecipient_clicked()
{
    ChooseStorage_Dialog ChooseDialog;
    ChooseDialog.setDialog(db);
    ChooseDialog.exec();

    if(ChooseDialog.getSelectedStorage().id != 0)
    {
        inv.storageRecipient = ChooseDialog.getSelectedStorage();
        ui->label_StorageRecipient->setText(inv.storageRecipient.title);
    }
}

void AddInvoice_Dialog::slot_pushButton_ClearStorageRecipient_clicked()
{
    inv.storageRecipient.id = 0;
    ui->label_StorageRecipient->setText("не задано");
}

void AddInvoice_Dialog::slot_pushButton_AddProduct_clicked()
{
    AddOrSetProductInInvoice_Dialog AddDialog;
    AddDialog.setConnection(db);
    AddDialog.exec();
    product tmp = AddDialog.getProduct();

    if(tmp.id != 0)
    {
        inv.listProducts.push_back(AddDialog.getProduct());
        updateTableProducts();
    }
}

void AddInvoice_Dialog::slot_pushButton_SetProduct_clicked()
{
    AddOrSetProductInInvoice_Dialog SetDialog;
    SetDialog.setConnection(db);
    SetDialog.setProduct(inv.listProducts.at(ui->tableWidget_Products->currentRow()));
    SetDialog.exec();
    inv.listProducts[ui->tableWidget_Products->currentRow()] = SetDialog.getProduct();
    updateTableProducts();
}

void AddInvoice_Dialog::slot_pushButton_DeleteProduct_clicked()
{
    inv.listProducts.removeAt(ui->tableWidget_Products->currentRow());
    updateTableProducts();
}

void AddInvoice_Dialog::updateTableProducts()
{
    ui->tableWidget_Products->setRowCount(0);

    for(int i = 0; i < inv.listProducts.size(); i++)
    {
        ui->tableWidget_Products->insertRow(ui->tableWidget_Products->rowCount());
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 0, new QTableWidgetItem(inv.listProducts.at(i).nomenclature));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 1, new QTableWidgetItem(inv.listProducts.at(i).title));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 2, new QTableWidgetItem(inv.listProducts.at(i).measuring));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 3, new QTableWidgetItem(QVariant(inv.listProducts.at(i).quantity).toString()));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 4, new QTableWidgetItem(QVariant(inv.listProducts.at(i).priceSender).toString()));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 5, new QTableWidgetItem(QVariant(inv.listProducts.at(i).price).toString()));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 6, new QTableWidgetItem(QVariant(inv.listProducts.at(i).priceSender*inv.listProducts.at(i).quantity).toString()));
        ui->tableWidget_Products->setItem(ui->tableWidget_Products->rowCount()-1, 7, new QTableWidgetItem(QVariant(inv.listProducts.at(i).price*inv.listProducts.at(i).quantity).toString()));
    }

    int sum = 0;

    for(int i = 0; i < inv.listProducts.size(); i++)
    {
        sum += inv.listProducts.at(i).priceSender*inv.listProducts.at(i).quantity;
    }

    ui->label_SumPayment->setText(QVariant(sum).toString());
}

void AddInvoice_Dialog::slot_pushButton_Save_clicked()
{
    inv.paymentType = db.getPaymentTypeById(ui->comboBox_TypePayment->currentIndex()+1);
    inv.typeInvoice = db.getTypeInvoiceById(ui->comboBox_TypeInvoice->currentIndex()+1);
    inv.note = ui->plainTextEdit_Note->toPlainText();
    inv.sum = QVariant(ui->label_SumPayment->text()).toFloat();
    inv.data = QDate::currentDate();
    inv.storno = 0;

    if(inv.listProducts.size() != 0)
        this->close();
}

invoice AddInvoice_Dialog::getInvoice()
{
    return inv;
}
