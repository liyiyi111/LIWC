
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
     * @brief 设置路口模式
     * @param mode 0-自动
     *              1-水平方向通行
     *              2-垂直方向通行
     *              3-禁行
     *              4-夜间
     */
    void setCrossingMode(int mode);




private slots:
    void flickerTimerTimeoutSlot();
    void crossingModeControlSlot(int crossingId, int mode);

    void runTimerTimeoutSlot();

private:
    static MainPage *obj;
    void paintEvent(QPaintEvent *);
    Ui::MainPage *ui;
    int crossingId = -1;
    int greenTime;
    int leftId;
    int rightId;
    int upId;
    int downId;
    int leftRoad;
    int rightRoad;
    int upRoad;
    int downRoad;
    int hcolor=0,vcolor=1;  //0-绿色，1-红色，2-黄色，3-关闭
    QTimer *flickerTimer;
    int lightFlickerIndex = 0;
    int mode = 0;
    int carId = -1;
    int endurance = 1000;
    int mileage = 0;
    QStringList roadList;
    int roadIndex;
    int roadPos;
    QTimer *runTimer;
};

#endif // MAINPAGE_H
