#ifndef ADDORSETPROVIDER_DIALOG_H
#define ADDORSETPROVIDER_DIALOG_H

#include <QDialog>

namespace Ui {
class AddOrSetProvider_Dialog;
}

class AddOrSetProvider_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrSetProvider_Dialog(QWidget *parent = nullptr);
    ~AddOrSetProvider_Dialog();

private:
    Ui::AddOrSetProvider_Dialog *ui;
};

#endif // ADDORSETPROVIDER_DIALOG_H
