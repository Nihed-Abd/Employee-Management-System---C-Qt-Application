#include "mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;

    bool test=c.createconnect();
    if(test)
    {
        w.setWindowTitle("RDI Center");
        w.show();
        QMessageBox::information(nullptr, QObject::tr("RDI Center."),
                    QObject::tr("Connection Successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



}
    else
        QMessageBox::critical(nullptr, QObject::tr("RDI Center."),
                    QObject::tr("Connection Failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
