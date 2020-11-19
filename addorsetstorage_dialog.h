#ifndef ADDORSETSTORAGE_DIALOG_H
#define ADDORSETSTORAGE_DIALOG_H

#include <QDialog>
#include "objectsdatabase.h"

namespace Ui {
class AddOrSetStorage_Dialog;
}

class AddOrSetStorage_Dialog : public QDialog
{
    Q_OBJECT
    storage st;

public:
    explicit AddOrSetStorage_Dialog(QWidget *parent = nullptr);
    ~AddOrSetStorage_Dialog();

    void setStorage(storage storage);
    storage getStorage();

private slots:
    void slot_pushButton_Save_clicked();

private:
    Ui::AddOrSetStorage_Dialog *ui;
};

#endif // ADDORSETSTORAGE_DIALOG_H
