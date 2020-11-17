#include "printpreview_dialog.h"
#include "ui_printpreview_dialog.h"

PrintPreview_Dialog::PrintPreview_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintPreview_Dialog)
{
    ui->setupUi(this);
}

PrintPreview_Dialog::~PrintPreview_Dialog()
{
    delete ui;
}
