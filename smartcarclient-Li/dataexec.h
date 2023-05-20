#ifndef DATAEXEC_H
#define DATAEXEC_H

#include <QObject>
class DataExec;
class Road{
public:
    friend class DataExec;
    Road(int id, int x, int y, int w, int h, int dir, int color);
    const int id;
    const int x,y;
    const int w,h;
    const int dir;//0-left, 1-right, 2-up, 3-down
    int getColor();
    void setColor(int color);
protected:
    int color;//0-green,1-red,2-yellow
};

class Light{
public:
    friend class DataExec;
    Light(int id, int roadId, int crossingId, int x, int y,
          int w, int h, int color);
    const int id;
    const int roadId;
    const int crossingId;
    const int x,y;
    const int w,h;
    int getColor();
    void setColor(int color);
protected:
    int color;//0-green,1-red,2-yellow
};

class Car{
public:
    friend class DataExec;
    Car(int id);
    const int id;
    void setPos(int roadId, int roadPos);
    void getPos(int &roadId, int &roadPos);

protected:
    int roadId = -1;    //未采集到数据
    int roadPos;
};


class DataExec : public QObject
{
    Q_OBJECT
protected:
    explicit DataExec(QObject *parent = nullptr);

public:
    static DataExec *getObject();
    QList<Road *> *getRoadList();
    QList<Light *> *getLightList();
    QList<Car *> *getCarList();
    bool getRoadInfo(int id, int &x, int &y, int &w, int &h, int &dir);

signals:
    void dataChanged();

protected slots:
    void carPosChangedSlot(int carId, int roadId,
                       int roadPos);
    void crossingLightChangedSlot(int id, int roadId, int color);

protected:
    Car *searchCar(int carId);
    Light *searchLight(int lightId);
    int getRoadCarNumber(int roadId);
    static DataExec *obj;
    QList<Road *> * roadList;
    QList<Light *> * lightList;
    QList<Car *> * carList;//实列化
};

#endif // DATAEXEC_H
