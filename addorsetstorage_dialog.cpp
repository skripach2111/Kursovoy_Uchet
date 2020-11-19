#include "addorsetstorage_dialog.h"
#include "ui_addorsetstorage_dialog.h"

AddOrSetStorage_Dialog::AddOrSetStorage_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrSetStorage_Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Save, SIGNAL(clicked()), this, SLOT(slot_pushButton_Save_clicked()));
}

AddOrSetStorage_Dialog::~AddOrSetStorage_Dialog()
{
    delete ui;
}

void AddOrSetStorage_Dialog::slot_pushButton_Save_clicked()
{
    st.title = "";
    st.city = "";
    st.address = "";
    st.capacity = 0;

    st.title = ui->lineEdit_Name->text();
    st.city = ui->lineEdit_Country->text();
    st.address = ui->lineEdit_Address->text();
    st.capacity = ui->spinBox_Capacity->value();

    if(st.title.size() != 0 && st.city.size() != 0 && st.address.size() != 0 && st.capacity != 0)
        this->close();
}

void AddOrSetStorage_Dialog::setStorage(storage storage)
{
    st.id = storage.id;
    ui->lineEdit_Name->setText(storage.title);
    ui->lineEdit_Country->setText(storage.city);
    ui->lineEdit_Address->setText(storage.address);
    ui->spinBox_Capacity->setValue(storage.capacity);
}

storage AddOrSetStorage_Dialog::getStorage()
{
    return st;
}
