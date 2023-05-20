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

void NetworkExec::lightChanged(int lightId, int roadId, int color)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 3001);
    obj.insert("light_id", lightId);
    obj.insert("road_id", roadId);
    obj.insert("color", color);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::crossingModeChanged(int crossingId, int mode)
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 4001);
    obj.insert("crossing_id", crossingId);
    obj.insert("mode", mode);
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
    if(type == 6001)
    {
        int id = obj.value("id").toInt();
        int mode = obj.value("mode").toInt();
        emit crossingModeControl(id, mode);
    }
}
