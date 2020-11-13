#include "mainwindow.h"
#include "authorization_dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    authorization_dialog *auth_dialog = new authorization_dialog;
    MainWindow *MWindow = new MainWindow;

    auth_dialog->exec();
    if(auth_dialog->Connected())
    {
        auth_dialog->close();
        return a.exec();
    }
    else
    {
        auth_dialog->close();
        return a.exec();
    }
}
