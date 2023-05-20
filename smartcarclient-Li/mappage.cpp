#include "mappage.h"
#include <QPainter>
#include <QPixmap>
#include "dataexec.h"
#include <QPen>
#include <QBrush>

MapPage::MapPage(QWidget *parent)
    : QWidget{parent}
{
    connect(DataExec::getObject(),
            &DataExec::dataChanged,
            this, &MapPage::dataChangedSlot);
}

void MapPage::setMapShow(bool roadDrawFlag, bool carDrawFlag, bool crossingDrawFlag)
{
    this->roadDrawFlag = roadDrawFlag;
    this->carDrawFlag = carDrawFlag;
    this->crossingDrawFlag = crossingDrawFlag;
    update();
}

void MapPage::dataChangedSlot()
{
    update();
    
}

void MapPage::paintEvent(QPaintEvent *)
{
    QPainter painter; //画师
    QPixmap img(":/Image/RoadMap.jpg");
    QPixmap img2(":/Image/car.png");

    if(img.isNull())
        return;

    QPen pen;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    painter.begin(&img);

    if(roadDrawFlag)
    {
        QList<Road *> *roadList =
            DataExec::getObject()->getRoadList();
        for(int i = 0; i < roadList->length(); i++)
        {
            Road *r = roadList->at(i);
            int color = r->getColor();
            pen.setColor(color == 0 ? Qt::green :
                         color == 1 ? Qt::red :
                         color == 2 ? Qt::yellow :
                             Qt::white);
            brush.setColor(color == 0 ? Qt::green :
                           color == 1 ? Qt::red :
                           color == 2 ? Qt::yellow :
                           Qt::white);
            painter.setPen(pen);
            painter.setBrush(brush);
            painter.drawRect(r->x, r->y, r->w, r->h);
        }
    }

    if(crossingDrawFlag)
    {
        QList<Light *> *lightList =
            DataExec::getObject()->getLightList();
        for(int i = 0; i < lightList->length(); i++)
        {
            Light *l = lightList->at(i);
            int color = l->getColor();
            pen.setColor(color == 0 ? Qt::green :
                             color == 1 ? Qt::red :
                             color == 2 ? Qt::yellow :
                             Qt::white);
            brush.setColor(color == 0 ? Qt::green :
                               color == 1 ? Qt::red :
                               color == 2 ? Qt::yellow :
                               Qt::white);
            painter.setPen(pen);
            painter.setBrush(brush);
            painter.drawRect(l->x, l->y, l->w, l->h);
        }
    }

    if(carDrawFlag)
    {
        QList<Car *> *carList =
            DataExec::getObject()->getCarList();
        for(int i = 0; i < carList->length(); i++)
        {
            Car *c = carList->at(i);
            int roadId, roadPos;
            c->getPos(roadId, roadPos);
            int x,y;
            if(roadId == -1)
            {
                if(c->id == 0)
                {
                    x = 638;
                    y = 572;
                }
                else if(c->id == 1)
                {
                    x = 638;
                    y = 616;
                }
                else
                {
                    x = 726;
                    y = 616;
                }
            }
            else
            {
                int rx, ry, rw, rh, rdir;
                bool ok = DataExec::getObject()->getRoadInfo(
                    roadId, rx, ry, rw, rh, rdir);
                if(!ok)
                    continue;
                if(rdir == 0)
                {
                    y = ry;
                    x = rx + rw - rw * roadPos / 100;
                }
                else if(rdir == 1)
                {
                    y = ry;
                    x = rx + rw * roadPos / 100;
                }
                else if(rdir == 2)
                {
                    x = rx;
                    y = ry + rh - rh * roadPos / 100;
                }
                else
                {
                    x = rx;
                    y = ry + rh * roadPos / 100;
                }
            }

            x -= 15;
            y -= 15;
            painter.drawPixmap(x, y, 30, 30, img2);
            pen.setColor(Qt::black);
            painter.setPen(pen);
            painter.setFont(QFont("Times", 12, QFont::Bold));
            painter.drawText(x+10, y+20, QString("%1").arg(c->id));
        }
    }

    painter.end();


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

