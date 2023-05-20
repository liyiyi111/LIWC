#include "zigbeeprotocol.h"
#include "zigbeedriver.h"
#include <QColor>
/*QByteArray是Qt框架中的一个类，用于处理字节数组。它可以存储任意类型的数据，并提供了一些方法来操作这些数据。在上述代码中，QByteArray被用于构建一个包含特定命令和颜色信息的字节数组，然后将其发送到串口。
 * 具体来说，data.append(QByteArray::fromHex(cmd.toLocal8Bit()))将一个十六进制字符串转换为字节数组并添加到data中，data.append(ug)、
 * data.append(ur)和data.append(ub)将颜色信息添加到data中，最后return ZigbeeDriver::getObject()->sendToSerialPort(data)将data发送到串口。*/
ZigbeeProtocol *ZigbeeProtocol::obj=nullptr;
ZigbeeProtocol::ZigbeeProtocol(QObject *parent) : QObject(parent)
{

}

ZigbeeProtocol *ZigbeeProtocol::getObject()
{
    if(obj == nullptr)
        obj = new ZigbeeProtocol;
    return obj;
}

bool ZigbeeProtocol::openLight1(int light)
{
    QString cmd = "FE FE 00 FF FF 0A 10 11 ";
    unsigned char l = (unsigned int)light;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(l);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::openLight2(int light)
{
    QString cmd = "FE FE 00 FF FF 0A 10 12 ";
    unsigned char l = (unsigned int)light;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(l);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::openLight3(int light)
{
    QString cmd = "FE FE 00 FF FF 0A 10 13 ";
    unsigned char l = (unsigned int)light;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(l);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::openLight4(int light)
{
    QString cmd = "FE FE 00 FF FF 0A 10 14 ";
    unsigned char l = (unsigned int)light;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(l);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::openRGBLight(int r, int g, int b)
{
    QString cmd = "FE FE 00 FF FF 0C 10 15 ";
    unsigned char ur = (unsigned int)r;
    unsigned char ug = (unsigned int)g;
    unsigned char ub = (unsigned int)b;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ug);
    data.append(ur);
    data.append(ub);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::openRGBLight(QColor color)
{
    //这段代码将颜色的红、绿、蓝值附加到命令字符串中，并将其转换为字节数组。最后，它将字节数组发送到串口。
    QString cmd = "FE FE 00 FF FF 0C 10 15 ";
    unsigned char ur = (unsigned int)color.red();
    unsigned char ug = (unsigned int)color.green();
    unsigned char ub = (unsigned int)color.blue();
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ug);
    data.append(ur);
    data.append(ub);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::alarmControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 50 21 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::alarmLedControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 50 22 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::steerengineControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 60 25 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::stepmotorControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 70 26 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::fanControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 70 27 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::relay1Control(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 70 28 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::relay2Control(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 70 29 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}

bool ZigbeeProtocol::lockControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 80 2A ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    return ZigbeeDriver::getObject()->sendToSerialPort(data);
}
