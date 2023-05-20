#include "configexec.h"
#include <QSettings>
#include <QDateTime>
#define CONFIGFILENAME      "config.ini"
#define DEFGROUPNAME        "settings"
#define SERVERIP            "server_ip"
#define SERVERPORT          "server_port"
#define CROSSINGID          "crossing_id"
#define LIGHTLEFTID         "light_left_id"
#define LIGHTRIGHTID        "light_right_id"
#define LIGHTUPID           "light_up_id"
#define LIGHTDOWNID         "light_down_id"
#define LIGHTLEFTROADID     "light_left_road_id"
#define LIGHTRIGHTROADID    "light_right_road_id"
#define LIGHTUPROADID       "light_up_road_id"
#define LIGHTDOWNROADID     "light_down_road_id"
#define CROSSINGGREENTIME   "crossing_green_time"
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

int ConfigExec::getCrossingId()
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    if(!set.allKeys().contains(CROSSINGID))
        set.setValue(CROSSINGID, 0);
    int re = set.value(CROSSINGID).toInt();
    set.endGroup();
    return re;
}

int ConfigExec::getCrossingGreenTime()
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    if(!set.allKeys().contains(CROSSINGGREENTIME))
        set.setValue(CROSSINGGREENTIME, 15);
    int re = set.value(CROSSINGGREENTIME).toInt();
    if(re < 5)
    {
        re = 5;
        set.setValue(CROSSINGGREENTIME, re);
    }
    set.endGroup();
    return re;
}

void ConfigExec::getLightConfig(int &leftId, int &rightId, int &upId, int &downId, int &leftRoad, int &rightRoad, int &upRoad, int &downRoad)
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    QStringList allkey = set.allKeys();
    if(!allkey.contains(LIGHTLEFTID))
        set.setValue(LIGHTLEFTID, -1);
    if(!allkey.contains(LIGHTRIGHTID))
        set.setValue(LIGHTRIGHTID, -1);
    if(!allkey.contains(LIGHTUPID))
        set.setValue(LIGHTUPID, -1);
    if(!allkey.contains(LIGHTDOWNID))
        set.setValue(LIGHTDOWNID, -1);
    if(!allkey.contains(LIGHTLEFTROADID))
        set.setValue(LIGHTLEFTROADID, -1);
    if(!allkey.contains(LIGHTRIGHTROADID))
        set.setValue(LIGHTRIGHTROADID, -1);
    if(!allkey.contains(LIGHTUPROADID))
        set.setValue(LIGHTUPROADID, -1);
    if(!allkey.contains(LIGHTDOWNROADID))
        set.setValue(LIGHTDOWNROADID, -1);
    leftId = set.value(LIGHTLEFTID).toInt();
    rightId = set.value(LIGHTRIGHTID).toInt();
    upId = set.value(LIGHTUPID).toInt();
    downId = set.value(LIGHTDOWNID).toInt();
    leftRoad = set.value(LIGHTLEFTROADID).toInt();
    rightRoad = set.value(LIGHTRIGHTROADID).toInt();
    upRoad = set.value(LIGHTUPROADID).toInt();
    downRoad = set.value(LIGHTDOWNROADID).toInt();

    set.endGroup();
}


QStringList ConfigExec::getCarRoadList()
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(DEFGROUPNAME);
    QStringList re = set.value(CARROADLIST).toStringList();
    if(re.isEmpty()){
        re << "6" << "10" ;
        set.setValue(CARROADLIST, re);
    }
    set.endGroup();
    return re;
}

//int ConfigExec::getCarEndurance()
//{
//    QSettings set(CONFIGFILENAME,
//                  QSettings::IniFormat);
//    set.beginGroup(DEFGROUPNAME);
//    if(!set.allKeys().contains(CARENDURANCE))
//        set.setValue(CARENDURANCE, 1000);
//    int re = set.value(CARENDURANCE).toInt();
//    set.endGroup();
//    return re;
//}

//int ConfigExec::getCarMileage()
//{
//    QSettings set(CONFIGFILENAME,
//                  QSettings::IniFormat);
//    set.beginGroup(DEFGROUPNAME);
//    if(!set.allKeys().contains(CARMILEAGE))
//        set.setValue(CARMILEAGE, 0);
//    int re = set.value(CARMILEAGE).toInt();
//    set.endGroup();
//    return re;
//}

//void ConfigExec::setCarEndurance(int endurance)
//{
//    QSettings set(CONFIGFILENAME,
//                  QSettings::IniFormat);
//    set.beginGroup(DEFGROUPNAME);
//    set.setValue(CARENDURANCE, endurance);
//    set.endGroup();
//}

//void ConfigExec::setCarMileage(int mileage)
//{
//    QSettings set(CONFIGFILENAME,
//                  QSettings::IniFormat);
//    set.beginGroup(DEFGROUPNAME);
//    set.setValue(CARMILEAGE, mileage);
//    set.endGroup();
//}

