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
     * @brief 获取车辆id
     * @return
     */
    int getCarId();
    /**
     * @brief 获取车辆key
     * @return
     */
    QString getCarKey();
    /**
     * @brief 获取续航
     * @return
     */
    int getCarEndurance();
    /**
     * @brief 获取里程
     * @return
     */
    int getCarMileage();
    /**
     * @brief 设置车辆续航
     * @param endurance
     */
    void setCarEndurance(int endurance);
    /**
     * @brief 设置车辆里程
     * @param mileage
     */
    void setCarMileage(int mileage);
    /**
     * @brief 获取车辆运行轨迹
     * @return
     */
    QStringList getCarRoadList();


protected:
    static ConfigExec *obj;

};

#endif // CONFIGEXEC_H
