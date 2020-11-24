#ifndef MOREABOUTINVOICE_DIALOG_H
#define MOREABOUTINVOICE_DIALOG_H

#include <QDialog>
#include "objectsdatabase.h"

namespace Ui {
class MoreAboutInvoice_Dialog;
}

class MoreAboutInvoice_Dialog : public QDialog
{
    Q_OBJECT
    invoice inv;

public:
    explicit MoreAboutInvoice_Dialog(QWidget *parent = nullptr);
    ~MoreAboutInvoice_Dialog();

    void setDialog(invoice invoice);

private:
    Ui::MoreAboutInvoice_Dialog *ui;
};

#endif // MOREABOUTINVOICE_DIALOG_H
