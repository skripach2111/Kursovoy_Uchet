#ifndef PRINTPREVIEW_DIALOG_H
#define PRINTPREVIEW_DIALOG_H

#include <QDialog>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>

namespace Ui {
class PrintPreview_Dialog;
}

class PrintPreview_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrintPreview_Dialog(QWidget *parent = nullptr);
    ~PrintPreview_Dialog();

    void setDialog(QString textForCheck, QString textForDocument);
    void exportToPDF(QString text);

private slots:
    void on_pushButton_ToPdfChek_clicked();

    void on_pushButton_ToPdfDocument_clicked();

    void on_pushButton_Exit_clicked();

private:
    Ui::PrintPreview_Dialog *ui;
};

#endif // PRINTPREVIEW_DIALOG_H
