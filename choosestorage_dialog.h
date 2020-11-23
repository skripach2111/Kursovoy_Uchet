#ifndef CHOOSESTORAGE_DIALOG_H
#define CHOOSESTORAGE_DIALOG_H

#include <QDialog>
#include "databasemodule.h"

namespace Ui {
class ChooseStorage_Dialog;
}

class ChooseStorage_Dialog : public QDialog
{
    Q_OBJECT
    storage st;
    DatabaseModule db;

public:
    explicit ChooseStorage_Dialog(QWidget *parent = nullptr);
    ~ChooseStorage_Dialog();

    void setDialog(DatabaseModule db_connection);
    storage getSelectedStorage();
    void searchingStorage();
    void updateTable(QList <storage> listStorages);

private slots:
    void slot_pushButton_Select_clicked();
    void slot_lineEdit_Title_textEdited();

private:
    Ui::ChooseStorage_Dialog *ui;
};

#endif // CHOOSESTORAGE_DIALOG_H
