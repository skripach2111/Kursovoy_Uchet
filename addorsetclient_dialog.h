#ifndef ADDORSETCLIENT_DIALOG_H
#define ADDORSETCLIENT_DIALOG_H

#include <QDialog>
#include "objectsdatabase.h"

namespace Ui {
class AddOrSetClient_Dialog;
}

class AddOrSetClient_Dialog : public QDialog
{
    Q_OBJECT
    client cl;

public:
    explicit AddOrSetClient_Dialog(QWidget *parent = nullptr);
    ~AddOrSetClient_Dialog();

    void setClient(client client);
    client getClient();

private slots:
        void slot_pushButton_Save_clicked();

private:
    Ui::AddOrSetClient_Dialog *ui;
};

#endif // ADDORSETCLIENT_DIALOG_H
