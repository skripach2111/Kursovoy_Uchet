#ifndef CHOOSECLIENT_DIALOG_H
#define CHOOSECLIENT_DIALOG_H

#include <QDialog>
#include "databasemodule.h"

namespace Ui {
class ChooseClient_Dialog;
}

class ChooseClient_Dialog : public QDialog
{
    Q_OBJECT
    client cl;
    DatabaseModule db;

public:
    explicit ChooseClient_Dialog(QWidget *parent = nullptr);
    ~ChooseClient_Dialog();

    void setDialog(DatabaseModule db_connection);
    client getSelectedClient();
    void searchingClient();
    void updateTable(QList <client> listClients);

private slots:
    void slot_pushButton_Select_clicked();
    void slot_lineEdit_Title_textEdited();

private:
    Ui::ChooseClient_Dialog *ui;
};

#endif // CHOOSECLIENT_DIALOG_H
