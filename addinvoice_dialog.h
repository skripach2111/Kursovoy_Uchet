#ifndef ADDINVOICE_DIALOG_H
#define ADDINVOICE_DIALOG_H

#include <QDialog>

namespace Ui {
class AddInvoice_Dialog;
}

class AddInvoice_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddInvoice_Dialog(QWidget *parent = nullptr);
    ~AddInvoice_Dialog();

private:
    Ui::AddInvoice_Dialog *ui;
};

#endif // ADDINVOICE_DIALOG_H
