#ifndef ADDORSETUSER_DIALOG_H
#define ADDORSETUSER_DIALOG_H

#include <QDialog>
#include "databasemodule.h"
#include "objectsdatabase.h"

namespace Ui {
class AddOrSetUser_Dialog;
}

class AddOrSetUser_Dialog : public QDialog
{
    Q_OBJECT
    user us;
    DatabaseModule db;

public:
    explicit AddOrSetUser_Dialog(QWidget *parent = nullptr);
    ~AddOrSetUser_Dialog();

    void setUser(user user);
    void setConnection(DatabaseModule db_connection);
    user getUser();

    void updateTableSelected();
    void updateTableAvialable();
    void updatePosition();
    void setCurrentPosition(int id);

private slots:
    void slot_pushButton_Save_clicked();
    void slot_pushButton_ToSelected_clicked();
    void slot_pushButton_ToAvialable_clicked();

private:
    Ui::AddOrSetUser_Dialog *ui;
};

#endif // ADDORSETUSER_DIALOG_H
