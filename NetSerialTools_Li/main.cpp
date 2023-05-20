#include "toolspage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToolsPage w;
    w.show();
    return a.exec();
}
