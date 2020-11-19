#ifndef CHOOSEPRODUCT_DIALOG_H
#define CHOOSEPRODUCT_DIALOG_H

#include <QDialog>
#include "objectsdatabase.h"
#include "databasemodule.h"

namespace Ui {
class ChooseProduct_Dialog;
}

class ChooseProduct_Dialog : public QDialog
{
    Q_OBJECT
    product pr;
    DatabaseModule db;

public:
    explicit ChooseProduct_Dialog(QWidget *parent = nullptr);
    ~ChooseProduct_Dialog();

    void setDialog(DatabaseModule db_connection);
    product getSelectedProduct();
    void searchingProducts();
    void updateTable(QList <product> listProducts);

private slots:
    void slot_pushButton_Enter_clicked();
    void slot_lineEdit_Nomenclature_textEdited();
    void slot_lineEdit_Name_textEdited();

private:
    Ui::ChooseProduct_Dialog *ui;
};

#endif // CHOOSEPRODUCT_DIALOG_H
