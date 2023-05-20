#include "networkexec.h"
#include <QTcpSocket>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include "configexec.h"
NetworkExec *NetworkExec::obj = nullptr;
NetworkExec::NetworkExec(QObject *parent)
    : QObject{parent}
    , client(new QTcpSocket)
{
    connect(client, &QTcpSocket::readyRead,
            this, &NetworkExec::clientReadyReadSlot);
    connectToHost();
}

NetworkExec *NetworkExec::getObject()
{
    if(obj == nullptr)
        obj = new NetworkExec;
    return obj;
}

void NetworkExec::sendClientType(int type)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 1000);
    obj.insert("client_type", type);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carLightChanged(int id, bool sw)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 2001);
    obj.insert("id", id);
    obj.insert("sw", sw);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carAlarmLightChanged(int id, bool sw)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 2002);
    obj.insert("id", id);
    obj.insert("sw", sw);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carEnduranceChanged(int id, int endurance)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 2003);
    obj.insert("id", id);
    obj.insert("endurance", endurance);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carMileageChanged(int id, int mileage)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 2004);
    obj.insert("id", id);
    obj.insert("mileage", mileage);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carNewWarning(int id, int warningId, QString warningMsg)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 2005);
    obj.insert("id", id);
    obj.insert("warning_id", warningId);
    obj.insert("warning_msg", warningMsg);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carRunChanged(int id, bool sw)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 2006);
    obj.insert("id", id);
    obj.insert("sw", sw);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carLockChanged(int id, bool sw)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 2007);
    obj.insert("id", id);
    obj.insert("sw", sw);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carPosChanged(int id, int roadId, int roadPos)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 2008);
    obj.insert("id", id);
    obj.insert("road_id", roadId);
    obj.insert("road_pos", roadPos);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::clientReadyReadSlot()
{
    QByteArray data = client->readAll();
    int count = 0;
    int left = 0;
    for(int i = 0; i < data.length(); i++)
    {
        if(data.at(i) == '{'){
            if(count == 0)
            {
                left = i;
            }
            count++;
        }
        else if(data.at(i) == '}'){
            count--;
            if(count == 0)
            {
                QByteArray temp =
                    data.mid(left, i-left+1);
                handleFrame(temp);
            }
        }
    }
}

void NetworkExec::connectToHost()
{
    client->connectToHost(
        ConfigExec::getObject()->getServerIp(),
        ConfigExec::getObject()->getServerPort());
    client->waitForConnected(2000);
}

void NetworkExec::handleFrame(const QByteArray &frame)
{
    QJsonObject obj = QJsonDocument::fromJson(frame)
            .object();
    int type = obj.value("type").toInt();
    if(type == 5001)
    {
        int id = obj.value("id").toInt();
        bool sw = obj.value("sw").toBool();
        QString key = obj.value("key").toString();
        emit carRunControl(id, sw, key);
    }
    else if(type == 5002)
    {
        int id = obj.value("id").toInt();
        bool sw = obj.value("sw").toBool();
        QString key = obj.value("key").toString();
        emit carLightControl(id, sw, key);
    }
    else if(type == 5003)
    {
        int id = obj.value("id").toInt();
        bool sw = obj.value("sw").toBool();
        QString key = obj.value("key").toString();
        emit carAlarmLightControl(id, sw, key);
    }
    else if(type == 5004)
    {
        int id = obj.value("id").toInt();
        bool sw = obj.value("sw").toBool();
        QString key = obj.value("key").toString();
        emit carLockControl(id, sw, key);
    }
    else if(type == 3001)
    {
        int lightId = obj.value("light_id").toInt();
        int roadId = obj.value("road_id").toInt();
        int color = obj.value("color").toInt();
        emit lightColorChanged(lightId, roadId, color);
    }
}
