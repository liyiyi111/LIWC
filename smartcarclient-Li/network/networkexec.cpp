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

void NetworkExec::carSetLock(int id, bool sw, QString key)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 5004);
    obj.insert("id", id);
    obj.insert("sw", sw);
    obj.insert("key", key);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carSetStart(int id, bool sw, QString key)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 5001);
    obj.insert("id", id);
    obj.insert("sw", sw);
    obj.insert("key", key);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carSetLight(int id, bool sw, QString key)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 5002);
    obj.insert("id", id);
    obj.insert("sw", sw);
    obj.insert("key", key);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::carSetAlarmLight(int id, bool sw, QString key)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 5003);
    obj.insert("id", id);
    obj.insert("sw", sw);
    obj.insert("key", key);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::crossingSetMode(int id, int mode)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 6001);
    obj.insert("id", id);
    obj.insert("mode", mode);
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
    if(type == 2001)
    {
        int id = obj.value("id").toInt();
        bool sw = obj.value("sw").toBool();
        emit carLightState(id, sw);
    }
    else if(type == 2002)
    {
        int id = obj.value("id").toInt();
        bool sw = obj.value("sw").toBool();
        emit carAlarmLightState(id, sw);
    }
    else if(type == 2003)
    {
        int id = obj.value("id").toInt();
        int endurance = obj.value("endurance").toInt();
        emit carEndurance(id, endurance);
    }
    else if(type == 2004)
    {
        int id = obj.value("id").toInt();
        int mileage = obj.value("mileage").toInt();
        emit carMileage(id, mileage);
    }
    else if(type == 2005)
    {
        int id = obj.value("id").toInt();
        int warnId = obj.value("warning_id").toInt();
        QString warnMsg = obj.value("warning_msg").toString();
        emit carWarning(id, warnId, warnMsg);
    }
    else if(type == 2006)
    {
        int id = obj.value("id").toInt();
        bool sw = obj.value("sw").toBool();
        emit carStartState(id, sw);
    }
    else if(type == 2007)
    {
        int id = obj.value("id").toInt();
        bool sw = obj.value("sw").toBool();
        emit carLockState(id, sw);
    }
    else if(type == 2008)
    {
        int id = obj.value("id").toInt();
        int roadId = obj.value("road_id").toInt();
        int roadPos = obj.value("road_pos").toInt();
        emit carPosChanged(id, roadId, roadPos);
    }
    else if(type == 3001)
    {
        int id = obj.value("light_id").toInt();
        int color = obj.value("color").toInt();
        int roadId = obj.value("roadId").toInt();
        emit crossingLightChanged(id, roadId, color);
    }
    else if(type == 4001)
    {
        int id = obj.value("crossing_id").toInt();
        int mode = obj.value("mode").toInt();
        emit crossingModeChanged(id, mode);
    }
}
