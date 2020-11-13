#ifndef AUTHORIZATION_DIALOG_H
#define AUTHORIZATION_DIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class authorization_dialog;
}

class authorization_dialog : public QDialog
{
    Q_OBJECT

    bool connected = false;
    QSqlDatabase db;

public:
    explicit authorization_dialog(QWidget *parent = nullptr);
    bool Connected();
    QSqlDatabase getConnection();
    ~authorization_dialog();
private slots:
    void slot_pushButton_login_clicked();
    void slot_pushButton_exit_clicked();

private:
    Ui::authorization_dialog *ui;
};

#endif // AUTHORIZATION_DIALOG_H
