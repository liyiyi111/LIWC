#include "configexec.h"
#include <QSettings>
#include <QDateTime>
#define CONFIGFILENAME  "config.ini"
#define DEFGROUPNAME    "settings"
#define SERVERIP        "server_ip"
#define SERVERPORT      "server_port"
#define CARID           "car_id"
#define CARKEY          "car_key"
#define CARENDURANCE    "car_endurance"
#define CARMILEAGE      "car_mileage"
#define CARROADLIST     "car_road_list"

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

int ConfigExec::getCarId()
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    if(!set.allKeys().contains(CARID))
        set.setValue(CARID, 0);
    int re = set.value(CARID).toInt();
    set.endGroup();
    return re;
}

QString ConfigExec::getCarKey()
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    if(!set.allKeys().contains(CARKEY)){
        QString temp;
        for(int i = 0; i < 16; i++)
        {
            temp.append(char(rand()%26 + 'a'));
        }
        set.setValue(CARKEY, temp);
    }
    QString re = set.value(CARKEY).toString();
    set.endGroup();
    return re;
}

int ConfigExec::getCarEndurance()
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    if(!set.allKeys().contains(CARENDURANCE))
        set.setValue(CARENDURANCE, 1000);
    int re = set.value(CARENDURANCE).toInt();
    set.endGroup();
    return re;
}

int ConfigExec::getCarMileage()
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    if(!set.allKeys().contains(CARMILEAGE))
        set.setValue(CARMILEAGE, 0);
    int re = set.value(CARMILEAGE).toInt();
    set.endGroup();
    return re;
}

void ConfigExec::setCarEndurance(int endurance)
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    set.setValue(CARENDURANCE, endurance);
    set.endGroup();
}

void ConfigExec::setCarMileage(int mileage)
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    set.setValue(CARMILEAGE, mileage);
    set.endGroup();
}

QStringList ConfigExec::getCarRoadList()
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    QStringList re = set.value(CARROADLIST).toStringList();
    if(re.isEmpty()){
        re << "0" << "6" << "10" << "5" << "13" << "9";
        set.setValue(CARROADLIST, re);
    }
    set.endGroup();
    return re;
}





