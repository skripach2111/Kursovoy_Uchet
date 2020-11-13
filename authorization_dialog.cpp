#include "authorization_dialog.h"
#include "ui_authorization_dialog.h"

authorization_dialog::authorization_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorization_dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_login, SIGNAL(clicked()), this, SLOT(slot_pushButton_login_clicked()));
    connect(ui->pushButton_exit, SIGNAL(clicked()), this, SLOT(slot_pushButton_exit_clicked()));
}

authorization_dialog::~authorization_dialog()
{
    delete ui;
}

void authorization_dialog::slot_pushButton_exit_clicked()
{
    connected = false;
    db.close();
    this->close();
}

bool authorization_dialog::Connected()
{
    return connected;
}

void authorization_dialog::slot_pushButton_login_clicked()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("baza");
    db.setUserName("userbaza");
    db.setPassword("password");
    if(db.open())
    {
        ui->label_error->setText("Подключено! Вход...");

        QSqlQuery query;
        query.prepare("SELECT password FROM users WHERE login = :l");
        query.bindValue(":l", ui->lineEdit_login->text());
        query.exec();

        if(query.size() == 0)
            ui->label_error->setText("Ошибка! Неверный логин или пароль.");
        else
        {
            connected = true;
            this->close();
        }
    }
    else
        ui->label_error->setText("Неудача! Связь не установлена.");
}

QSqlDatabase authorization_dialog::getConnection()
{
    return db;
}
