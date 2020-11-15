#ifndef CHOOSEPRODUCT_DIALOG_H
#define CHOOSEPRODUCT_DIALOG_H

#include <QDialog>

namespace Ui {
class ChooseProduct_Dialog;
}

class ChooseProduct_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseProduct_Dialog(QWidget *parent = nullptr);
    ~ChooseProduct_Dialog();

private:
    Ui::ChooseProduct_Dialog *ui;
};

#endif // CHOOSEPRODUCT_DIALOG_H
