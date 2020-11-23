#ifndef CHOOSEPROVIDER_DIALOG_H
#define CHOOSEPROVIDER_DIALOG_H

#include <QDialog>
#include "databasemodule.h"

namespace Ui {
class ChooseProvider_Dialog;
}

class ChooseProvider_Dialog : public QDialog
{
    Q_OBJECT
    DatabaseModule db;
    provider pr;

public:
    explicit ChooseProvider_Dialog(QWidget *parent = nullptr);
    ~ChooseProvider_Dialog();

    void setDialog(DatabaseModule db_connection);
    provider getSelectedProvider();
    void searchingProvider();
    void updateTable(QList <provider> listProviders);

private slots:
    void slot_pushButton_Select_clicked();
    void slot_lineEdit_Title_textEdited();

private:
    Ui::ChooseProvider_Dialog *ui;
};

#endif // CHOOSEPROVIDER_DIALOG_H
