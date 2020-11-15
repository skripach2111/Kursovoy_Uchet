#ifndef MOREABOUTINVOICE_DIALOG_H
#define MOREABOUTINVOICE_DIALOG_H

#include <QDialog>

namespace Ui {
class MoreAboutInvoice_Dialog;
}

class MoreAboutInvoice_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoreAboutInvoice_Dialog(QWidget *parent = nullptr);
    ~MoreAboutInvoice_Dialog();

private:
    Ui::MoreAboutInvoice_Dialog *ui;
};

#endif // MOREABOUTINVOICE_DIALOG_H
