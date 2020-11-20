#ifndef ADDORSETPRODUCT_DIALOG_H
#define ADDORSETPRODUCT_DIALOG_H

#include <QDialog>
#include "objectsdatabase.h"

namespace Ui {
class AddOrSetProduct_Dialog;
}

class AddOrSetProduct_Dialog : public QDialog
{
    Q_OBJECT
    product pr;

public:
    explicit AddOrSetProduct_Dialog(QWidget *parent = nullptr);
    ~AddOrSetProduct_Dialog();

    void setProduct(product product);
    product getProduct();

private slots:
    void slot_pushButton_Save_clicked();

private:
    Ui::AddOrSetProduct_Dialog *ui;
};

#endif // ADDORSETPRODUCT_DIALOG_H
