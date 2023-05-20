#include "configexec.h"
#include <QSettings>
#include <QDateTime>
#define CONFIGFILENAME      "config.ini"
#define DEFGROUPNAME        "settings"
#define SERVERIP            "server_ip"
#define SERVERPORT          "server_port"

ConfigExec *ConfigExec::obj = nullptr;
ConfigExec::ConfigExec(QObject *parent)
    : QObject{parent}
{
    srand(QDateTime::currentDateTime()
              .toSecsSinceEpoch());

}

ConfigExec *ConfigExec::getObject()
{
    if(obj == nullptr)
        obj = new ConfigExec;
    return obj;
}

QString ConfigExec::getServerIp()
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    if(!set.allKeys().contains(SERVERIP))
        set.setValue(SERVERIP, "127.0.0.1");
    QString re = set.value(SERVERIP).toString();
    set.endGroup();
    return re;
}

int ConfigExec::getServerPort()
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    if(!set.allKeys().contains(SERVERPORT))
        set.setValue(SERVERPORT, 20001);
    int re = set.value(SERVERPORT).toInt();
    set.endGroup();
    return re;
}

void ConfigExec::setServerConfig(QString ip, int port)
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    set.setValue(SERVERIP, ip);
    set.setValue(SERVERPORT, port);
    set.endGroup();

}

