
#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>


class QTimer;
QT_BEGIN_NAMESPACE
namespace Ui { class MainPage; }
QT_END_NAMESPACE

class MainPage : public QWidget

{
    Q_OBJECT

private:
    MainPage(QWidget *parent = nullptr);

public:
    static MainPage *getObject();
    ~MainPage();
    /**
     * @brief 大灯控制
     * @param sw
     */
    void carLightControl(bool sw);
    /**
     * @brief 双闪控制
     * @param sw
     */
    void carAlarmLightControl(bool sw);
    /**
     * @brief 解锁
     */
    void carUnlock();
    /**
     * @brief 上锁
     */
    void carLock();
    /**
     * @brief 启动
     */
    void carStart();
    /**
     * @brief 停止
     */
    void carStop();

private slots:
    void alarmLightTimerTimeoutSlot();
    void carLightControlSlot(int id, bool sw, QString key);
    void carAlarmLightControlSlot(int id, bool sw, QString key);
    void carLockControlSlot(int id, bool sw, QString key);
    void carRunControlSlot(int id, bool sw, QString key);
    void lightColorChangedSlot(int lightId, int roadId, int color);
    void runTimerTimeoutSlot();
    void on_btnAlarm_clicked();

private:
    static MainPage *obj;
    void paintEvent(QPaintEvent *);
    Ui::MainPage *ui;
    QTimer *alarmLightTimer;
    bool alarmLightState = false;   //双闪状态
    bool lightState = false;        //大灯状态
    bool lockState = false;         //锁定状态
    bool runState = false;          //运行状态
    QTimer *runTimer;
    int carId = -1;
    QString key;
    int endurance = 1000;
    int mileage = 0;
    QStringList roadList;
    int roadIndex;
    int roadPos;
    QHash<int, int> lightColor;
};

#endif // MAINPAGE_H
