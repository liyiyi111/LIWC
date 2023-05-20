#include "mainpage.h"
#include "ui_mainpage.h"
#include <QPainter>
#include <QPixmap>
#include "networkexec.h"
#include <QTimer>
#include "configexec.h"

MainPage *MainPage::obj = nullptr;
MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
    , flickerTimer(new QTimer)
    ,runTimer(new QTimer)
{
    ui->setupUi(this);

    NetworkExec *exec = NetworkExec::getObject();
    connect(exec, &NetworkExec::crossingModeControl,
            this, &MainPage::crossingModeControlSlot);

    crossingId = ConfigExec::getObject()->getCrossingId();
    setWindowTitle(QString("路口：%1").arg(crossingId));
    greenTime = ConfigExec::getObject()->getCrossingGreenTime();
    ConfigExec::getObject()->getLightConfig(
        leftId, rightId, upId, downId, leftRoad, rightRoad, upRoad, downRoad);
    resize(400, 300);

    NetworkExec::getObject()->sendClientType(1);
    connect(flickerTimer, &QTimer::timeout,
            this, &MainPage::flickerTimerTimeoutSlot);
    connect(runTimer,&QTimer::timeout,this,&MainPage::runTimerTimeoutSlot);
    flickerTimer->start(500);
    setCrossingMode(0);



     roadList = ConfigExec::getObject()->getCarRoadList();




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

void MainPage::setCrossingMode(int mode)
{
    this->mode = mode;
    lightFlickerIndex = 0;
    NetworkExec::getObject()->crossingModeChanged(crossingId, mode);
    setWindowTitle(QString("路口：%1，模式：%2")
                       .arg(crossingId)
                   .arg(mode == 0 ? "自动" :
                        mode == 1 ? "水平通行" :
                        mode == 2 ? "垂直通行" :
                        mode == 3 ? "禁止通行" :
                        mode == 4 ? "自由通行" :
                                    "未知"));
}



void MainPage::flickerTimerTimeoutSlot()
{
    if(mode == 0){
        if(lightFlickerIndex < (greenTime - 3) * 2)
        {
            hcolor = 0;
            vcolor = 1;
        }
        else if(lightFlickerIndex < greenTime * 2)
        {
            hcolor = lightFlickerIndex % 2 == 1 ? 0 : 3;
            vcolor = 1;
        }
        else if(lightFlickerIndex < (greenTime + 3) * 2)
        {
            hcolor = lightFlickerIndex % 2 == 1 ? 2 : 3;
            vcolor = 1;
        }
        else if(lightFlickerIndex < (greenTime * 2) * 2)
        {
            hcolor = 1;
            vcolor = 0;
        }
        else if(lightFlickerIndex < (greenTime * 2 + 3) * 2)
        {
            hcolor = 1;
            vcolor = lightFlickerIndex % 2 == 1 ? 0 : 3;
        }
        else
        {
            hcolor = 1;
            vcolor = lightFlickerIndex % 2 == 1 ? 2 : 3;
        }
        lightFlickerIndex++;
        if(lightFlickerIndex > (greenTime + 3) * 2 * 2)
        {
            lightFlickerIndex = 0;
            return;
        }
    }
    else if(mode == 1)
    {
        hcolor = 0;
        vcolor = 1;
    }
    else if(mode == 2)
    {
        hcolor = 1;
        vcolor = 0;
    }
    else if(mode == 3)
    {
        hcolor = 1;
        vcolor = 1;
    }
    else if(mode == 4)
    {
        hcolor = lightFlickerIndex % 2 == 1 ? 2 : 3;
        vcolor = hcolor;
        lightFlickerIndex++;
        if(lightFlickerIndex >= 1000)
            lightFlickerIndex = 0;
    }
    this->update();
    NetworkExec *exec = NetworkExec::getObject();
    if(leftId >= 0)
    {
        exec->lightChanged(leftId, leftRoad, hcolor);
    }
    if(rightId >= 0)
    {
        exec->lightChanged(rightId, rightRoad, hcolor);
    }
    if(upId >= 0)
    {
        exec->lightChanged(upId, upRoad, vcolor);
    }
    if(downId >= 0)
    {
        exec->lightChanged(downId, downRoad, vcolor);
    }
}

void MainPage::crossingModeControlSlot(int crossingId, int mode)
{
    if(crossingId != this->crossingId)
        return;
    setCrossingMode(mode);
}

void MainPage::paintEvent(QPaintEvent *)
{
    QPainter painter; //画师
    QPixmap img(":/Image/background.jpg");
    QPen gpen, rpen, ypen, wpen;
    QBrush gbrush, rbrush, ybrush, wbrush;
    ypen.setColor(Qt::yellow);
    ybrush.setColor(Qt::yellow);
    ybrush.setStyle(Qt::SolidPattern);
    gpen.setColor(Qt::green);
    gbrush.setColor(Qt::green);
    gbrush.setStyle(Qt::SolidPattern);
    rpen.setColor(Qt::red);
    rbrush.setColor(Qt::red);
    rbrush.setStyle(Qt::SolidPattern);
    wpen.setColor(Qt::white);
    wbrush.setColor(Qt::white);
    wbrush.setStyle(Qt::SolidPattern);

    painter.begin(&img);

    if(leftId >= 0)
    {
        painter.setPen(hcolor == 0 ? gpen :
                           hcolor == 1 ? rpen :
                           hcolor == 2 ? ypen :
                           wpen);
        painter.setBrush(hcolor == 0 ? gbrush :
                           hcolor == 1 ? rbrush :
                           hcolor == 2 ? ybrush :
                           wbrush);
        painter.drawRect(53, 78, 12, 68);
    }
    if(rightId >= 0)
    {
        painter.setPen(hcolor == 0 ? gpen :
                           hcolor == 1 ? rpen :
                           hcolor == 2 ? ypen :
                           wpen);
        painter.setBrush(hcolor == 0 ? gbrush :
                             hcolor == 1 ? rbrush :
                             hcolor == 2 ? ybrush :
                             wbrush);
        painter.drawRect(165, 78, 12, 68);
    }
    if(upId >= 0)
    {
        painter.setPen(vcolor == 0 ? gpen :
                           vcolor == 1 ? rpen :
                           vcolor == 2 ? ypen :
                           wpen);
        painter.setBrush(vcolor == 0 ? gbrush :
                             vcolor == 1 ? rbrush :
                             vcolor == 2 ? ybrush :
                             wbrush);
        painter.drawRect(80, 48, 68, 12);
    }
    if(downId >= 0)
    {
        painter.setPen(vcolor == 0 ? gpen :
                           vcolor == 1 ? rpen :
                           vcolor == 2 ? ypen :
                           wpen);
        painter.setBrush(vcolor == 0 ? gbrush :
                             vcolor == 1 ? rbrush :
                             vcolor == 2 ? ybrush :
                             wbrush);
        painter.drawRect(80, 163, 68, 12);
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

void MainPage::runTimerTimeoutSlot()
{
//    int roadId = QString(roadList.at(roadIndex)).toInt();
//    if(roadId >= 6)
//        roadPos += 25;
//    else
//        roadPos += 10;

    NetworkExec::getObject()
        ->carPosChanged(carId,
                QString(roadList.at(roadIndex)).toInt(),
                roadPos);
}





