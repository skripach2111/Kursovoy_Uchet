#ifndef ADDORSETSTORAGE_DIALOG_H
#define ADDORSETSTORAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class AddOrSetStorage_Dialog;
}

class AddOrSetStorage_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrSetStorage_Dialog(QWidget *parent = nullptr);
    ~AddOrSetStorage_Dialog();

private:
    Ui::AddOrSetStorage_Dialog *ui;
};

#endif // ADDORSETSTORAGE_DIALOG_H
