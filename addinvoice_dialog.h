#ifndef ADDINVOICE_DIALOG_H
#define ADDINVOICE_DIALOG_H

#include <QDialog>
#include "databasemodule.h"
#include "chooseclient_dialog.h"
#include "chooseproduct_dialog.h"
#include "chooseprovider_dialog.h"
#include "choosestorage_dialog.h"
#include "chooseuser_dialog.h"
#include "addorsetproductininvoice_dialog.h"

namespace Ui {
class AddInvoice_Dialog;
}

class AddInvoice_Dialog : public QDialog
{
    Q_OBJECT
    DatabaseModule db;
    invoice inv;

public:
    explicit AddInvoice_Dialog(QWidget *parent = nullptr);
    ~AddInvoice_Dialog();

    void setDialog(DatabaseModule db_connection);
    invoice getInvoice();

    void updateTypeInvoice();
    void updateTableProducts();
    //void updateTypePayment();

private slots:
    void slot_comboBox_TypePayment_currentIndexChanged(int index);
    void slot_pushButton_SetSender_clicked();
    void slot_pushButton_SetRecipient_clicked();
    void slot_pushButton_SetStorageSender_clicked();
    void slot_pushButton_SetStorageRecipient_clicked();
    void slot_pushButton_ClearSender_clicked();
    void slot_pushButton_ClearRecipient_clicked();
    void slot_pushButton_ClearStorageSender_clicked();
    void slot_pushButton_ClearStorageRecipient_clicked();
    void slot_pushButton_AddProduct_clicked();
    void slot_pushButton_SetProduct_clicked();
    void slot_pushButton_DeleteProduct_clicked();
    void slot_pushButton_Save_clicked();

private:
    Ui::AddInvoice_Dialog *ui;
};

#endif // ADDINVOICE_DIALOG_H
