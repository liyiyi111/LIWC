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
     * @brief 获取路口id
     * @return
     */
    int getCrossingId();
    /**
     * @brief 获取绿灯时间，单位秒
     * @return
     */
    int getCrossingGreenTime();
    /**
     * @brief 获取信号灯配置
     * @param leftId
     * @param rightId
     * @param topId
     * @param bottomId
     * @param leftRoad
     * @param rightRoad
     * @param topRoad
     * @param bottomRoad
     */
    void getLightConfig(int &leftId, int &rightId, int &upId, int &downId,
                        int &leftRoad, int &rightRoad, int &upRoad, int &downRoad);



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



     QStringList getCarRoadList();


protected:
    static ConfigExec *obj;

};

#endif // CONFIGEXEC_H
