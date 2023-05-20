#include "play.h"
#include "ui_play.h"
#include "QFileDialog" //文件快捷方式
#include "QFileDevice" //文件设备
#include <QFileInfo> //Q文件信息
#include <QMediaPlayer>
#include <QMediaPlaylist> //Q媒体播放列表
#include <QListWidget>
Play::Play(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Play)
{
    ui->setupUi(this);
    play = new QMediaPlayer;
    playList = new QMediaPlaylist;
    duration = 0;
    durationTime = '00:00';

    //建立播放列表;
    play->setPlaylist(playList);
    //顺序播放
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    connect(playList,&QMediaPlaylist::currentIndexChanged,this,&Play::playListCurrentIndexChangedSlot);

    connect(play,&QMediaPlayer::durationChanged,this,&Play::playerDurationChangedSlot);
    connect(play,&QMediaPlayer::positionChanged,this,&Play::playerPositionChangedSlot);
}

Play::~Play()
{
    delete ui;
    delete playList;
    delete play;
}

void Play::on_btnAdd_clicked()
{
    QStringList list = QFileDialog::getOpenFileNames(this,"选择音乐","D://","音乐文件(*.mp3 *.wav)");
    for(int i =0; i<list.length();i++)
    {

//        ui->LwMusicList->addItem(QFileInfo::fileName(list.at(i)));
        ui->LwMusicList->addItem(
                    QFileInfo(list.at(i)).fileName());
        playList->addMedia(QUrl::fromLocalFile(list.at(i)));
    }
    //isEmpty将所选项目恢复到其原始位置空
    if(!playList->isEmpty())
    {
        playList->setCurrentIndex(-1); //设置当前索引
        ui->LwMusicList->setCurrentRow(-1); //设置当前行
        return;
    }
    playList->setCurrentIndex(0);
    ui->LwMusicList->setCurrentRow(0);
}

void Play::on_btnPlay_clicked()
{
    play->play();
}

void Play::on_btnPvry_clicked()
{
    playList->previous(); //上一次的
}

void Play::playListCurrentIndexChangedSlot(int position)
{
    ui->LwMusicList->setCurrentRow(0);

}

void Play::on_btnPlayBackMode_clicked()
{
    //playbackMode播放模式
    if(playList->playbackMode() ==
        QMediaPlaylist::Loop)
        {//切换为随机
            playList->setPlaybackMode(
                        QMediaPlaylist::Random);
            ui->btnPlayBackMode->setText("随机播放");

        }
    else if(playList->playbackMode() ==
               QMediaPlaylist::Random)

        {//切换为随机
            playList->setPlaybackMode(
                        QMediaPlaylist::CurrentItemInLoop);
            ui->btnPlayBackMode->setText("单曲播放");


        }
    else
        {
            playList->setPlaybackMode(
                        QMediaPlaylist::Loop);
            ui->btnPlayBackMode->setText("循环播放");
        }

}

void Play::playerPositionChangedSlot(qint64 position)
{
    //进度条 0-100
    int pos;
    if(duration <= 0)
        pos = 0;
    else
        //它将当前播放位置乘以100，然后除以总时长，以获得一个0到100的百分比。这个百分比被设置为UI上的进度条位置
        pos = position *100 /duration;
    ui->hsPlayPos->setValue(pos);
    //计算时间;
    int m,s;
    //这段代码通过计算音频播放的位置来计算时间。首先，它将毫秒转换为分钟和秒，然后将它们格式化为“分：秒”的字符串。最后，它将这个字符串设置为UI上的标签。
    m = position / 1000/60;
    s = position / 1000 % 60;
//    int pos =position*100/duration;
    QString temp =QString("%1:%2").arg(m,2,10,QLatin1Char('0')).arg(s,2,10,QLatin1Char('0')).arg(durationTime);
    ui->lbPlayTime->setText(temp);


}


void Play::playerDurationChangedSlot(qint64 duration)
{
    this->duration=duration;
    if(duration <= 0)
    {
        durationTime = '00:00';
        return;
    }
    int m,s;
    m = duration / 1000/ 60;
    s = duration /1000 %60;

    durationTime = QString("%1:%2").arg(m,2,10,QLatin1Char('0')).arg(s,2,10,QLatin1Char('0'));
}


void Play::on_btnNext_clicked()
{
    playList->next();

}

//void Play::on_hsPlayPos_actionTriggered(int action)
//{
//    qDebug() << "on_hsPlayPos_actionTriggered";

//}


void Play::on_hsPlayPos_sliderReleased()
{
    qint64 pos = ui->hsPlayPos->value();
    qint64 position = pos * duration /100;
    play->setPosition(position);
}
