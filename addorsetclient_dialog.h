#ifndef ADDORSETCLIENT_DIALOG_H
#define ADDORSETCLIENT_DIALOG_H

#include <QDialog>

namespace Ui {
class AddOrSetClient_Dialog;
}

class AddOrSetClient_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrSetClient_Dialog(QWidget *parent = nullptr);
    ~AddOrSetClient_Dialog();

private:
    Ui::AddOrSetClient_Dialog *ui;
};

#endif // ADDORSETCLIENT_DIALOG_H
