#ifndef ADDORSETPRODUCTININVOICE_DIALOG_H
#define ADDORSETPRODUCTININVOICE_DIALOG_H

#include <QDialog>

namespace Ui {
class AddOrSetProductInInvoice_Dialog;
}

class AddOrSetProductInInvoice_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrSetProductInInvoice_Dialog(QWidget *parent = nullptr);
    ~AddOrSetProductInInvoice_Dialog();

private:
    Ui::AddOrSetProductInInvoice_Dialog *ui;
};

#endif // ADDORSETPRODUCTININVOICE_DIALOG_H
