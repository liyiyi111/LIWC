#include "mainpage.h"
#include "networkexec.h"
#include <QApplication>
#include "configexec.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigExec::getObject();
    NetworkExec::getObject();
    MainPage::getObject()->show();
    return a.exec();
}
