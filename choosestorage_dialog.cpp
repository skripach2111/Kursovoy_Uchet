#include "choosestorage_dialog.h"
#include "ui_choosestorage_dialog.h"

ChooseStorage_Dialog::ChooseStorage_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseStorage_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Select, SIGNAL(clicked()), this, SLOT(slot_pushButton_Select_clicked()));
    connect(ui->lineEdit_Title, SIGNAL(textEdited(QString)), this, SLOT(slot_lineEdit_Title_textEdited()));
}

ChooseStorage_Dialog::~ChooseStorage_Dialog()
{
    delete ui;
}

void ChooseStorage_Dialog::setDialog(DatabaseModule db_connection)
{
    db = db_connection;
    updateTable(db.getListStorages());
}

void ChooseStorage_Dialog::updateTable(QList<storage> listStorages)
{
    ui->listWidget_Storages->clear();

    for(int i = 0; i < listStorages.size(); i++)
        ui->listWidget_Storages->addItem(listStorages.at(i).title);
}

void ChooseStorage_Dialog::searchingStorage()
{
    QList <storage> listStorages = db.getListStorages();
    QList <storage> listStoragesSearch;

    for(int i = 0; i < listStorages.size(); i++)
        if(listStorages.at(i).title.indexOf(ui->lineEdit_Title->text()) > -1)
            listStoragesSearch.push_back(listStorages.at(i));

    updateTable(listStoragesSearch);
}

void ChooseStorage_Dialog::slot_lineEdit_Title_textEdited()
{
    searchingStorage();
}

void ChooseStorage_Dialog::slot_pushButton_Select_clicked()
{
    QList <storage> listStorages = db.getListStorages();

    for(int i = 0; i < listStorages.size(); i++)
        if(listStorages.at(i).title == ui->listWidget_Storages->currentItem()->text())
        {
            st = listStorages.at(i);
            i = listStorages.size();
        }

    this->close();
}

storage ChooseStorage_Dialog::getSelectedStorage()
{
    return st;
}
