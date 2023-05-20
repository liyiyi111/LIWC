
#ifndef MAPPAGE_H
#define MAPPAGE_H


#include <QWidget>


class MapPage : public QWidget
{
    Q_OBJECT
public:
    explicit MapPage(QWidget *parent = nullptr);
    void setMapShow(bool roadDrawFlag,
                    bool carDrawFlag,
                    bool crossingDrawFlag);

protected slots:
    void dataChangedSlot();

protected:
    void paintEvent(QPaintEvent *);
    bool roadDrawFlag = true;
    bool carDrawFlag = true;
    bool crossingDrawFlag = true;

};

#endif // MAPPAGE_H
