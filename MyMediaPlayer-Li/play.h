#ifndef PLAY_H
#define PLAY_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
namespace Ui {
class Play;
class QMediaPlayer;
class QMediaPlaylist;
}

class Play : public QWidget
{
    Q_OBJECT

public:
    explicit Play(QWidget *parent = 0);
    ~Play();

private slots:
    void on_btnAdd_clicked();

    void on_btnPlay_clicked();

    void on_btnNext_clicked();

    void on_btnPvry_clicked();

    void playListCurrentIndexChangedSlot(int position);

    void on_btnPlayBackMode_clicked();

    void playerPositionChangedSlot(qint64 position);
    void playerDurationChangedSlot(qint64 duration);


    void on_hsPlayPos_actionTriggered(int action);

    void on_hsPlayPos_sliderReleased();

private:
    Ui::Play *ui;
    QMediaPlayer *play;
    QMediaPlaylist *playList;
    qint64  duration;
    QString  durationTime;

};

#endif // PLAY_H
