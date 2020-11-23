#include "chooseprovider_dialog.h"
#include "ui_chooseprovider_dialog.h"

ChooseProvider_Dialog::ChooseProvider_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseProvider_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Select, SIGNAL(clicked()), this, SLOT(slot_pushButton_Select_clicked()));
    connect(ui->lineEdit_Title, SIGNAL(textEdited(QString)), this, SLOT(slot_lineEdit_Title_textEdited()));
}

ChooseProvider_Dialog::~ChooseProvider_Dialog()
{
    delete ui;
}

void ChooseProvider_Dialog::setDialog(DatabaseModule db_connection)
{
    db = db_connection;
    updateTable(db.getListProviders());
}

void ChooseProvider_Dialog::updateTable(QList<provider> listProviders)
{
    ui->listWidget_Providers->clear();

    for(int i = 0; i < listProviders.size(); i++)
        ui->listWidget_Providers->addItem(listProviders.at(i).title);
}

void ChooseProvider_Dialog::searchingProvider()
{
    QList <provider> listProviders = db.getListProviders();
    QList <provider> listProvidersSearch;

    for(int i = 0; i < listProviders.size(); i++)
        if(listProviders.at(i).title.indexOf(ui->lineEdit_Title->text()) > -1)
            listProvidersSearch.push_back(listProviders.at(i));

    updateTable(listProvidersSearch);
}

void ChooseProvider_Dialog::slot_lineEdit_Title_textEdited()
{
    searchingProvider();
}

void ChooseProvider_Dialog::slot_pushButton_Select_clicked()
{
    QList <provider> listProviders = db.getListProviders();

    for(int i = 0; i < listProviders.size(); i++)
        if(listProviders.at(i).title == ui->listWidget_Providers->currentItem()->text())
        {
            pr = listProviders.at(i);
            i = listProviders.size();
        }

    this->close();
}

provider ChooseProvider_Dialog::getSelectedProvider()
{
    return pr;
}
