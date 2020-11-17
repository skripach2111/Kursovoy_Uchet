#ifndef PRINTPREVIEW_DIALOG_H
#define PRINTPREVIEW_DIALOG_H

#include <QDialog>

namespace Ui {
class PrintPreview_Dialog;
}

class PrintPreview_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrintPreview_Dialog(QWidget *parent = nullptr);
    ~PrintPreview_Dialog();

private:
    Ui::PrintPreview_Dialog *ui;
};

#endif // PRINTPREVIEW_DIALOG_H
