#ifndef ADDORSETPRODUCTININVOICE_DIALOG_H
#define ADDORSETPRODUCTININVOICE_DIALOG_H

#include <QDialog>
#include "chooseproduct_dialog.h"
#include "databasemodule.h"

namespace Ui {
class AddOrSetProductInInvoice_Dialog;
}

class AddOrSetProductInInvoice_Dialog : public QDialog
{
    Q_OBJECT
    DatabaseModule db;
    product pr;

public:
    explicit AddOrSetProductInInvoice_Dialog(QWidget *parent = nullptr);
    ~AddOrSetProductInInvoice_Dialog();

    void setProduct(product product);
    void setConnection(DatabaseModule db_connection);
    product getProduct();
    void updateSum();

private slots:
    void slot_pushButton_ChooseProduct_clicked();
    void slot_pushButton_Enter_clicked();
    void slot_spinBox_NumberUnits_editingFinished();
    void slot_doubleSpinBox_PriceUnitsPurchase_editingFinished();

private:
    Ui::AddOrSetProductInInvoice_Dialog *ui;
};

#endif // ADDORSETPRODUCTININVOICE_DIALOG_H
