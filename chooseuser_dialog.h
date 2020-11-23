#ifndef CHOOSEUSER_DIALOG_H
#define CHOOSEUSER_DIALOG_H

#include <QDialog>
#include "databasemodule.h"

namespace Ui {
class ChooseUser_Dialog;
}

class ChooseUser_Dialog : public QDialog
{
    Q_OBJECT
    DatabaseModule db;
    user us;

public:
    explicit ChooseUser_Dialog(QWidget *parent = nullptr);
    ~ChooseUser_Dialog();

    void setDialog(DatabaseModule db_connection);
    user getSelectedUser();
    void searchingUser();
    void updateTable(QList <user> listUsers);

private slots:
    void slot_pushButton_Select_clicked();
    void slot_lineEdit_PIB_textEdited();

private:
    Ui::ChooseUser_Dialog *ui;
};

#endif // CHOOSEUSER_DIALOG_H
