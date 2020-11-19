#include "chooseproduct_dialog.h"
#include "ui_chooseproduct_dialog.h"

ChooseProduct_Dialog::ChooseProduct_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseProduct_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Enter, SIGNAL(clicked()), this, SLOT(slot_pushButton_Enter_clicked()));
    connect(ui->lineEdit_Name, SIGNAL(textEdited()), this, SLOT(slot_lineEdit_Name_textEdited()));
    connect(ui->lineEdit_Nomenclature, SIGNAL(textEdited()), this, SLOT(slot_lineEdit_Nomenclature_textEdited()));
}

ChooseProduct_Dialog::~ChooseProduct_Dialog()
{
    delete ui;
}

void ChooseProduct_Dialog::setDialog(DatabaseModule db_connection)
{
    db = db_connection;
    updateTable(db.getListProducts());
}

void ChooseProduct_Dialog::updateTable(QList<product> listProducts)
{
    ui->tableWidget_ListProducts->setRowCount(0);

    for(int i = 0; i < listProducts.size(); i++)
    {
        ui->tableWidget_ListProducts->insertRow(ui->tableWidget_ListProducts->rowCount());
        ui->tableWidget_ListProducts->setItem(ui->tableWidget_ListProducts->rowCount()-1, 0, new QTableWidgetItem(listProducts.at(i).nomenclature));
        ui->tableWidget_ListProducts->setItem(ui->tableWidget_ListProducts->rowCount()-1, 1, new QTableWidgetItem(listProducts.at(i).title));
        ui->tableWidget_ListProducts->setItem(ui->tableWidget_ListProducts->rowCount()-1, 2, new QTableWidgetItem(listProducts.at(i).measuring));
        ui->tableWidget_ListProducts->setItem(ui->tableWidget_ListProducts->rowCount()-1, 3, new QTableWidgetItem(listProducts.at(i).price));
    }
}

void ChooseProduct_Dialog::searchingProducts()
{
    QList <product> listProducts = db.getListProducts();
    QList <product> listProductsSearh;

    if(ui->lineEdit_Name->text().size() != 0 && ui->lineEdit_Name->text().size() != 0)
    {
            for(int i = 0; i < listProducts.size(); i++)
            {
                if(listProducts.at(i).title.indexOf(ui->lineEdit_Name->text()) > -1 && listProducts.at(i).nomenclature.indexOf(ui->lineEdit_Nomenclature->text()))
                    listProductsSearh.push_back(listProducts.at(i));
            }
    }
    else if(ui->lineEdit_Name->text().size() != 0 && ui->lineEdit_Name->text().size() == 0)
    {
        for(int i = 0; i < listProducts.size(); i++)
        {
            if(listProducts.at(i).title.indexOf(ui->lineEdit_Name->text()) > -1)
                listProductsSearh.push_back(listProducts.at(i));
        }
    }
    else if(ui->lineEdit_Name->text().size() == 0 && ui->lineEdit_Name->text().size() != 0)
    {
            for(int i = 0; i < listProducts.size(); i++)
            {
                if(listProducts.at(i).nomenclature.indexOf(ui->lineEdit_Nomenclature->text()))
                    listProductsSearh.push_back(listProducts.at(i));
            }
    }

    updateTable(listProductsSearh);
}

void ChooseProduct_Dialog::slot_lineEdit_Name_textEdited()
{
    searchingProducts();
}

void ChooseProduct_Dialog::slot_lineEdit_Nomenclature_textEdited()
{
    searchingProducts();
}

void ChooseProduct_Dialog::slot_pushButton_Enter_clicked()
{
    QList <product> listProducts = db.getListProducts();

    for(int i = 0; i < listProducts.size(); i++)
    {
        if(listProducts.at(i).nomenclature == ui->tableWidget_ListProducts->itemAt(ui->tableWidget_ListProducts->currentRow(), 0)->text())
        {
            pr = listProducts.at(i);
            i = listProducts.size();
        }
    }
}
