#include "dataexec.h"
#include "networkexec.h"
DataExec *DataExec::obj = nullptr;
DataExec::DataExec(QObject *parent)
    : QObject{parent}
    , roadList(new QList<Road *>)
    , lightList(new QList<Light *>)
    , carList(new QList<Car *>)
{
    roadList->append(new Road(0, 96, 27, 648, 3, 0, 0));
    roadList->append(new Road(1, 96, 59, 648, 3, 1, 0));
    roadList->append(new Road(2, 96, 347, 648, 3, 0, 0));
    roadList->append(new Road(3, 96, 379, 648, 3, 1, 0));
    roadList->append(new Road(4, 96, 671, 648, 3, 0, 0));
    roadList->append(new Road(5, 96, 703, 648, 3, 1, 0));
    roadList->append(new Road(6, 27, 96, 3, 220, 3, 0));
    roadList->append(new Road(7, 59, 96, 3, 220, 2, 0));
    roadList->append(new Road(8, 783, 96, 3, 220, 3, 0));
    roadList->append(new Road(9, 815, 96, 3, 220, 2, 0));
    roadList->append(new Road(10, 27, 420, 3, 220, 3, 0));
    roadList->append(new Road(11, 59, 420, 3, 220, 2, 0));
    roadList->append(new Road(12, 783, 420, 3, 220, 3, 0));
    roadList->append(new Road(13, 815, 420, 3, 220, 2, 0));

    lightList->append(new Light(0, 6, 0, 15, 333, 28, 3, 0));
    lightList->append(new Light(1, 2, 0, 76, 335, 3, 28, 0));
    lightList->append(new Light(2, 11, 0, 46, 400, 28, 3, 0));

    lightList->append(new Light(3, 8, 1, 770, 333, 28, 3, 0));
    lightList->append(new Light(4, 13, 1, 801, 400, 28, 3, 0));
    lightList->append(new Light(5, 3, 1, 761, 366, 3, 28, 0));

    carList->append(new Car(0));
    carList->append(new Car(1));
    carList->append(new Car(2));
    carList->append(new Car(3));

    NetworkExec *exec = NetworkExec::getObject();
    connect(exec, &NetworkExec::carPosChanged,
            this, &DataExec::carPosChangedSlot);
    connect(exec, &NetworkExec::crossingLightChanged,
            this, &DataExec::crossingLightChangedSlot);
}

DataExec *DataExec::getObject()
{
    if(obj == nullptr)
        obj = new DataExec;
    return obj;
}

QList<Road *> *DataExec::getRoadList()
{
    return roadList;
}

QList<Light *> *DataExec::getLightList()
{
    return lightList;
}

QList<Car *> *DataExec::getCarList()
{
    return carList;
}

bool DataExec::getRoadInfo(int id, int &x, int &y, int &w, int &h, int &dir)
{
    for(int i = 0; i < roadList->length(); i++)
    {
        if(roadList->at(i)->id == id)
        {
            Road *r = roadList->at(i);
            x = r->x;
            y = r->y;
            w = r->w;
            h = r->h;
            dir = r->dir;
            return true;
        }
    }
    return false;
}

void DataExec::carPosChangedSlot(int carId, int roadId, int roadPos)
{
    Car *c = searchCar(carId);
    if(c == nullptr)
        return;
    c->setPos(roadId, roadPos);
    for(int i = 0; i < roadList->length(); i++)
    {
        int count = getRoadCarNumber(
            roadList->at(i)->id);
        roadList->at(i)->setColor(count == 0 ? 0 :
                                  count == 1 ? 2 :
                                  1);
    }
    emit dataChanged();
}

void DataExec::crossingLightChangedSlot(int id, int roadId, int color)
{
    Light *l = searchLight(id);
    if(l == nullptr)
        return;
    l->setColor(color);
    emit dataChanged();
}

Car *DataExec::searchCar(int carId)
{
    Car *c = nullptr;
    for(int i = 0; i < carList->length(); i++)
    {
        if(carList->at(i)->id == carId)
            return carList->at(i);
    }
    return c;
}

Light *DataExec::searchLight(int lightId)
{
    Light *l = nullptr;
    for(int i = 0; i < lightList->length(); i++)
    {
        if(lightList->at(i)->id == lightId)
            return lightList->at(i);
    }
    return l;
}

int DataExec::getRoadCarNumber(int roadId)
{
    int count = 0;
    for(int i = 0; i < carList->length(); i++)
    {
        if(carList->at(i)->roadId == roadId)
            count++;
    }
    return count;
}

Road::Road(int id, int x, int y, int w, int h, int dir, int color)
    : id(id), x(x), y(y), w(w), h(h), dir(dir), color(color)
{

}

int Road::getColor()
{
    return color;
}

void Road::setColor(int color)
{
    this->color = color;
}

Light::Light(int id, int roadId, int crossingId, int x, int y, int w, int h, int color)
    : id(id), roadId(roadId), crossingId(crossingId), x(x), y(y), w(w), h(h), color(color)
{

}

int Light::getColor()
{
    return color;
}

void Light::setColor(int color)
{
    this->color = color;
}

Car::Car(int id)
    : id(id)
{

}

void Car::setPos(int roadId, int roadPos)
{
    this->roadId = roadId;
    this->roadPos = roadPos;
}

void Car::getPos(int &roadId, int &roadPos)
{
    roadId = this->roadId;
    roadPos = this->roadPos;
}
