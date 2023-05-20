#include "zigbeedriver.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
ZigbeeDriver *ZigbeeDriver::obj=nullptr;
ZigbeeDriver::ZigbeeDriver(QObject *parent) : QObject(parent)
  ,zigbee(new QSerialPort)
{

}

ZigbeeDriver *ZigbeeDriver::getObject()
{
    if(obj == nullptr)
        obj = new ZigbeeDriver;
    return obj;
}

QStringList ZigbeeDriver::getSerialPortList()
{
    QStringList list;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        list.append(info.portName());
    }
    return list;
}

bool ZigbeeDriver::openSerialPort(QString name, quint16 baudrate)
{
    if(zigbee->isOpen())
        zigbee->close();
    zigbee->setPortName(name);
    zigbee->setBaudRate(baudrate);
    zigbee->setDataBits(
       QSerialPort::DataBits::Data8);
    zigbee->setStopBits(
        QSerialPort::OneStop);
    zigbee->setParity(QSerialPort::NoParity);
    zigbee->setFlowControl(QSerialPort::NoFlowControl);
    bool ok = zigbee->open(QIODevice::ReadWrite);
    if(!ok)
        return false;
    else
        return true;
}

bool ZigbeeDriver::sendToSerialPort(const QByteArray &data)
{

    if(!zigbee->isOpen())
    {
        return false;
    }
    else{
        zigbee->write(data);
        return true;
    }

}

void ZigbeeDriver::closeSerialPort()
{
    if(zigbee->isOpen())
        zigbee->close();

}

bool ZigbeeDriver::getSerialPortStatus()
{
    if(!zigbee->isOpen()){
        return false;
    }
    else
        return true;
}
