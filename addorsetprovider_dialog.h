#ifndef ADDORSETPROVIDER_DIALOG_H
#define ADDORSETPROVIDER_DIALOG_H

#include <QDialog>
#include "objectsdatabase.h"

namespace Ui {
class AddOrSetProvider_Dialog;
}

class AddOrSetProvider_Dialog : public QDialog
{
    Q_OBJECT
    provider pr;

public:
    explicit AddOrSetProvider_Dialog(QWidget *parent = nullptr);
    ~AddOrSetProvider_Dialog();

    void setProvider(provider provider);
    provider getProvider();

private slots:
    void slot_pushButton_Save_clicked();

private:
    Ui::AddOrSetProvider_Dialog *ui;
};

#endif // ADDORSETPROVIDER_DIALOG_H
