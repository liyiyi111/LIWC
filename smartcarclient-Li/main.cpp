#include "mainpage.h"
#include "configexec.h"
#include "networkexec.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigExec::getObject();
    NetworkExec::getObject();
    MainPage w;
    w.show();
    return a.exec();
}
