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
     * @brief 车辆锁定
     * @param id 车辆id
     * @param sw
     * @param key 密钥
     */
    void carSetLock(int id, bool sw, QString key);
    /**
     * @brief 车辆运行控制
     * @param id
     * @param sw
     * @param key
     */
    void carSetStart(int id, bool sw, QString key);
    /**
     * @brief 车辆大灯设置
     * @param id
     * @param sw
     * @param key
     */
    void carSetLight(int id, bool sw, QString key);
    /**
     * @brief 车辆双闪设置
     * @param id
     * @param sw
     * @param key
     */
    void carSetAlarmLight(int id, bool sw, QString key);
    /**
     * @brief 路口模式设置
     * @param id
     * @param mode
     */
    void crossingSetMode(int id, int mode);

signals:
    void carPosChanged(int carId, int roadId,
                       int roadPos);
    void crossingLightChanged(int id, int roadId, int color);

    void carLightState(int carId, bool sw);
    void carAlarmLightState(int carId, bool sw);
    void carLockState(int carId, bool sw);
    void carStartState(int carId, bool sw);
    void carEndurance(int carId, int endurance);
    void carMileage(int carId, int mileage);
    void carWarning(int carId, int warnId,
                    QString warnMsg);
    void crossingModeChanged(int crossingId, int mode);


protected slots:
    void clientReadyReadSlot();

protected:
    void connectToHost();
    void handleFrame(const QByteArray &frame);

    static NetworkExec *obj;
    QTcpSocket *client;
};

#endif // NETWORKEXEC_H
