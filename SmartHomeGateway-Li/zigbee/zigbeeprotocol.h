#ifndef ZIGBEEPROTOCOL_H
#define ZIGBEEPROTOCOL_H

#include <QObject>
/**
 * @brief The Zigbee协议类
 */
class ZigbeeProtocol : public QObject
{
    Q_OBJECT
protected:
    explicit ZigbeeProtocol(QObject *parent = nullptr);
public:
    static ZigbeeProtocol *getObject();
    bool openLight1(int light);
    bool openLight2(int light);
    /**
     * @brief 控制LED灯 3
     * @param light 亮度0-255
     * @return
     */
    bool openLight3(int light);
    bool openLight4(int light);
    /**
     * @brief 控制炫彩LED灯
     * @param r
     * @param g
     * @param b
     * @return
     */
    bool openRGBLight(int r, int g, int b);
    bool openRGBLight(QColor color);
    /**
     * @brief 报警器的控制
     * @param status
     * @return
     */
    bool alarmControl(int status);
    /**
     * @brief 报警灯的控制
     * @param status
     * @return
     */
    bool alarmLedControl(int status);
    /**
     * @brief 舵机的控制
     * @param status
     * @return
     */
    bool steerengineControl(int status);
    /**
     * @brief 步进电机的控制
     * @param status
     * @return
     */
    bool stepmotorControl(int status);
    /**
     * @brief 风扇的控制
     * @param status
     * @return
     */
    bool fanControl(int status);
    /**
     * @brief 继电器1的控制
     * @param status
     * @return
     */
    bool relay1Control(int status);
    /**
     * @brief 继电器2的控制
     * @param status
     * @return
     */
    bool relay2Control(int status);
    /**
     * @brief 电磁锁的控制
     * @param status
     * @return
     */
    bool lockControl(int status);
signals:

public slots:
protected:
    static ZigbeeProtocol *obj;
};

#endif // ZIGBEEPROTOCOL_H
