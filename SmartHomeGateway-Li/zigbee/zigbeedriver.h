#ifndef ZIGBEEDRIVER_H
#define ZIGBEEDRIVER_H

#include <QObject>
class QSerialPort;
/**
 * @brief Zigbee 驱动类
 */
class ZigbeeDriver : public QObject
{
    Q_OBJECT
protected:
    explicit ZigbeeDriver(QObject *parent = nullptr);
public:
    static ZigbeeDriver *getObject();
    /**
     * @brief 获取可用串口列表
     * @return
     */
    QStringList getSerialPortList();
    /**
     * @brief 打开串口
     * @param name  串口名称
     * @param baudrate  波特率
     * @return
     */
    bool openSerialPort(QString name, quint16 baudrate);
    /**
     * @brief 向串口发送数据
     * @param data
     * @return
     */
    bool sendToSerialPort(const QByteArray &data);
    /**
     * @brief 关闭串口
     */
    void closeSerialPort();
    /**
     * @brief 获取串口状态
     * @return
     */
    bool getSerialPortStatus();
signals:

public slots:
protected:
    static ZigbeeDriver *obj;
    QSerialPort *zigbee;
};

#endif // ZIGBEEDRIVER_H
