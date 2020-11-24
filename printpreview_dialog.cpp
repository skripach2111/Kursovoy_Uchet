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

void PrintPreview_Dialog::setDialog(QString textForCheck, QString textForDocument)
{
    ui->plainTextEdit_PreviewChek->setPlainText(textForCheck);
    ui->plainTextEdit_2->setPlainText(textForDocument);
}

void PrintPreview_Dialog::exportToPDF(QString text)
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "%HOMEPATH%\\test", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName); // устанавливаем путь к pdf файлу

        QTextDocument doc;
        //doc.setHtml("<h1>" + ui->label_Tests->text() + "</h1>");
        doc.setPlainText(text);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);

        //    // работаем с отрисовкой pdf через QPainter
        //    QPainter p(&printer);
        //    // выполняем действия с p
        //    p.setBrush(QBrush(Qt::white, Qt::SolidPattern));
        //    p.drawText(0, 0, ui->label_Tests->text());
        //    p.end();
}

void PrintPreview_Dialog::on_pushButton_ToPdfChek_clicked()
{
    exportToPDF(ui->plainTextEdit_PreviewChek->toPlainText());
}

void PrintPreview_Dialog::on_pushButton_ToPdfDocument_clicked()
{
    exportToPDF(ui->plainTextEdit_2->toPlainText());
}

void PrintPreview_Dialog::on_pushButton_Exit_clicked()
{

}
