#ifndef ADDORSETUSER_DIALOG_H
#define ADDORSETUSER_DIALOG_H

#include <QDialog>

namespace Ui {
class AddOrSetUser_Dialog;
}

class AddOrSetUser_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrSetUser_Dialog(QWidget *parent = nullptr);
    ~AddOrSetUser_Dialog();

private:
    Ui::AddOrSetUser_Dialog *ui;
};

#endif // ADDORSETUSER_DIALOG_H
