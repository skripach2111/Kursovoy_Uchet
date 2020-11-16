#ifndef ADDORSETPRODUCT_DIALOG_H
#define ADDORSETPRODUCT_DIALOG_H

#include <QDialog>

namespace Ui {
class AddOrSetProduct_Dialog;
}

class AddOrSetProduct_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrSetProduct_Dialog(QWidget *parent = nullptr);
    ~AddOrSetProduct_Dialog();

private:
    Ui::AddOrSetProduct_Dialog *ui;
};

#endif // ADDORSETPRODUCT_DIALOG_H
