#include "mainpage.h"
#include "ui_mainpage.h"
#include <QPainter>
#include <QPixmap>
#include "networkexec.h"
#include <QTimer>
#define ROOTKEY "root123"
#include "configexec.h"

MainPage *MainPage::obj = nullptr;
MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
    , alarmLightTimer(new QTimer)
    , runTimer(new QTimer)
{
    ui->setupUi(this);
    connect(alarmLightTimer, &QTimer::timeout,
            this, &MainPage::alarmLightTimerTimeoutSlot);
    connect(runTimer, &QTimer::timeout,
            this, &MainPage::runTimerTimeoutSlot);

    NetworkExec *exec = NetworkExec::getObject();
    connect(exec, &NetworkExec::carAlarmLightControl,
            this, &MainPage::carAlarmLightControlSlot);
    connect(exec, &NetworkExec::carLightControl,
            this, &MainPage::carLightControlSlot);
    connect(exec, &NetworkExec::carLockControl,
            this, &MainPage::carLockControlSlot);
    connect(exec, &NetworkExec::carRunControl,
            this, &MainPage::carRunControlSlot);
    connect(exec, &NetworkExec::lightColorChanged,
            this, &MainPage::lightColorChangedSlot);

    carId = ConfigExec::getObject()->getCarId();

    setWindowTitle(QString("车辆：%1").arg(carId));
    resize(400, 300);

    key = ConfigExec::getObject()->getCarKey();
    endurance = ConfigExec::getObject()->getCarEndurance();
    mileage = ConfigExec::getObject()->getCarMileage();
    carLock();
    NetworkExec::getObject()->sendClientType(0);

    roadList = ConfigExec::getObject()->getCarRoadList();
    if(roadList.isEmpty())
        return;
    roadIndex = 0;
    roadPos = 0;
}

MainPage *MainPage::getObject()
{
    if(obj == nullptr)
        obj = new MainPage;
    return obj;
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::carLightControl(bool sw)
{
    lightState = sw;
    this->update();
    NetworkExec::getObject()->carLightChanged(carId, sw);
}

void MainPage::carAlarmLightControl(bool sw)
{
    if(sw)
    {//打开双闪
        if(!alarmLightTimer->isActive())
            alarmLightTimer->start(500);
    }
    else
    {//关闭双闪
        if(alarmLightTimer->isActive())
            alarmLightTimer->stop();
        alarmLightState = false;
    }
    this->update();
    NetworkExec::getObject()->carAlarmLightChanged(carId, sw);
}

void MainPage::carUnlock()
{
    lockState = false;
    this->setWindowTitle(QString("车辆：%1，已解锁")
                             .arg(carId));
    NetworkExec::getObject()->carLockChanged(carId, false);
}

void MainPage::carLock()
{
    lockState = true;
    this->setWindowTitle(QString("车辆：%1，上锁")
                             .arg(carId));
    NetworkExec::getObject()->carLockChanged(carId, true);
}

void MainPage::carStart()
{
    if(lockState)
        return;
//    runState = true;
    if(roadList.isEmpty())
        return;
    if(!runTimer->isActive())
        runTimer->start(600);
    NetworkExec::getObject()->carRunChanged(carId, true);
}

void MainPage::carStop()
{
    if(runTimer->isActive())
        runTimer->stop();
    NetworkExec::getObject()->carRunChanged(carId, false);
}

void MainPage::alarmLightTimerTimeoutSlot()
{
    if(alarmLightState)
        alarmLightState = false;
        
    else
        alarmLightState = true;
    this->update();
}

void MainPage::carLightControlSlot(int id, bool sw, QString key)
{
    if(id != carId || (key != this->key
                        && key != ROOTKEY))
        return;
    carLightControl(sw);
}

void MainPage::carAlarmLightControlSlot(int id, bool sw, QString key)
{
    if(id != carId || (key != this->key
                        && key != ROOTKEY))
        return;
    carAlarmLightControl(sw);
}

void MainPage::carLockControlSlot(int id, bool sw, QString key)
{
    if(id != carId || (key != this->key
                        && key != ROOTKEY))
        return;
    if(sw)
        carLock();
    else
        carUnlock();
}

void MainPage::carRunControlSlot(int id, bool sw, QString key)
{
    if(id != carId || (key != this->key
                        && key != ROOTKEY))
        return;
    if(sw && lockState == false)
        carStart();
    else if(!sw)
        carStop();
}

void MainPage::lightColorChangedSlot(int lightId, int roadId, int color)
{
    Q_UNUSED(lightId);
    lightColor.insert(roadId, color);
    if(color =0)
        carStop();
}

void MainPage::paintEvent(QPaintEvent *)
{
    QPainter painter; //画师
    QPixmap img(":/Image/car.png");
    QPen pen;
    QBrush brush;
    painter.begin(&img);

    pen.setColor(Qt::yellow);
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    if(lightState){
        painter.drawEllipse(17, 112, 35, 36);
        painter.drawEllipse(216, 112, 35, 36);
    }
    if(alarmLightState){
        painter.drawRect(17, 155, 35, 15);
        painter.drawRect(216, 155, 35, 15);
    }

    painter.end();

    if(img.isNull())
        return;
    int iw = img.width();
    int ih = img.height();
    painter.begin(this);
    int w = this->width();
    int h = this->height();
    int dx, dy, dw, dh;
    //绘制图片
    if(iw*h > ih*w){//图片比较宽
        dw = w;
        dh = w*ih/iw;
        dx = 0;
        dy = (h-dh)/2;
    }
    else{//图片比较高
        dw = h*iw/ih;
        dh = h;
        dx = (w-dw)/2;
        dy = 0;
    }
    painter.drawPixmap(dx,dy, dw,dh, img);
    painter.end();
}

void MainPage::on_btnAlarm_clicked()
{
    int wi = rand() % 3;
    NetworkExec::getObject()
        ->carNewWarning(carId,
                        wi,
                        wi == 0 ? "发动机" :
                        wi == 1 ? "变速箱" :
                        wi == 2 ? "胎压" : "未知");
}

void MainPage::runTimerTimeoutSlot()
{
    int roadId = QString(roadList.at(roadIndex)).toInt();
    if(roadId >= 6)
        roadPos += 25;
    else
        roadPos += 10;
    if(roadPos > 100)
    {
        if(lightColor.value(roadId, 0) != 0)
        {
            return;
        }
        roadIndex ++;
        if(roadIndex >= roadList.length())
            roadIndex = 0;
        roadPos=0;
    }
    mileage++;
    endurance--;
    if(endurance <= 0)
        endurance = 1000;
    ConfigExec::getObject()->setCarMileage(mileage);
    ConfigExec::getObject()->setCarEndurance(endurance);
    NetworkExec::getObject()
        ->carMileageChanged(carId, mileage);
    NetworkExec::getObject()
        ->carEnduranceChanged(carId, endurance);
    NetworkExec::getObject()
        ->carPosChanged(carId,
                QString(roadList.at(roadIndex)).toInt(),
                roadPos);
}






