#ifndef CONFIGEXEC_H
#define CONFIGEXEC_H
#include <QObject>

class ConfigExec : public QObject
{
    Q_OBJECT
protected:
    explicit ConfigExec(QObject *parent = nullptr);

public:
    static ConfigExec *getObject();
    /**
     * @brief 获取服务器ip
     * @return
     */
    QString getServerIp();
    /**
     * @brief 获取服务器端口
     * @return
     */
    int getServerPort();
    /**
     * @brief 保存服务器配置
     * @param ip
     * @param port
     */
    void setServerConfig(QString ip, int port);

protected:
    static ConfigExec *obj;

};

#endif // CONFIGEXEC_H
