#ifndef NETWORKEXEC_H
#define NETWORKEXEC_H

#include <QObject>
#include <QDateTime>
#include <QJsonArray>
class QTcpSocket;
class QTimer;
class NetworkExec : public QObject
{
    Q_OBJECT
protected:
    explicit NetworkExec(QObject *parent = nullptr);

public:
    static NetworkExec *getObject();
    /**
     * @brief 发送客户端身份
     * @param type
     */
    void sendClientType(int type);
    /**
     * @brief 车辆大灯状态改变
     * @param id
     * @param sw
     */
    void carLightChanged(int id, bool sw);
    /**
     * @brief 车辆双闪改变
     * @param id
     * @param sw
     */
    void carAlarmLightChanged(int id, bool sw);
    /**
     * @brief 车辆续航改变
     * @param id
     * @param endurance
     */
    void carEnduranceChanged(int id, int endurance);
    /**
     * @brief 车辆里程改变
     * @param id
     * @param mileage
     */
    void carMileageChanged(int id, int mileage);
    /**
     * @brief 车辆产生新的故障
     * @param id
     * @param warningId
     * @param warningMsg
     */
    void carNewWarning(int id, int warningId, QString warningMsg);
    /**
     * @brief 车辆运行状态改变
     * @param id
     * @param sw
     */
    void carRunChanged(int id, bool sw);
    /**
     * @brief 车辆锁定状态改变
     * @param id
     * @param sw
     */
    void carLockChanged(int id, bool sw);
    /**
     * @brief 车辆位置改变
     * @param id
     * @param roadId
     * @param roadPos
     */
    void carPosChanged(int id, int roadId, int roadPos);

signals:
    void carLightControl(int id, bool sw, QString key);
    void carAlarmLightControl(int id, bool sw, QString key);
    void carLockControl(int id, bool sw, QString key);
    void carRunControl(int id, bool sw, QString key);
    void lightColorChanged(int lightId, int roadId, int color);

protected slots:
    void clientReadyReadSlot();

protected:
    void connectToHost();
    void handleFrame(const QByteArray &frame);

    static NetworkExec *obj;
    QTcpSocket *client;
};

#endif // NETWORKEXEC_H
