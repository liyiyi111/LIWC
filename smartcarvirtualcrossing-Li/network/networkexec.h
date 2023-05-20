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
     * @brief 信号灯颜色改变
     * @param lightId
     * @param roadId
     * @param color
     */
    void lightChanged(int lightId, int roadId, int color);
    /**
     * @brief 路口模式改变
     * @param corssingId
     * @param mode
     */
    void crossingModeChanged(int crossingId, int mode);


    void carPosChanged(int id, int roadId, int roadPos);








signals:
    void crossingModeControl(int crossingId, int mode);



protected slots:
    void clientReadyReadSlot();

protected:
    void connectToHost();
    void handleFrame(const QByteArray &frame);

    static NetworkExec *obj;
    QTcpSocket *client;
};

#endif // NETWORKEXEC_H
