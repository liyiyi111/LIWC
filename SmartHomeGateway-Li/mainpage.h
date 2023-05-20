#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = 0);
    ~MainPage();

private slots:
    void on_btnOpenSerial_clicked();

    void on_btnSend_clicked();

    void on_hsLight3_sliderReleased();

    void on_hsLight1_sliderReleased();

    void on_hsLight2_sliderReleased();

    void on_hsLight4_sliderReleased();

    void on_btnAlarmOpen_clicked();

    void on_btnAlarmClose_clicked();

    void on_btnAlarmLedOpen_clicked();

    void on_btnAlarmLedClose_clicked();

    void on_btnSteerengineOpen_clicked();

    void on_btnSteerengineClose_clicked();

    void on_btnStepmotorOpen_clicked();

    void on_btnStepmotorClose_clicked();

    void on_btnFanOpen_clicked();

    void on_btnFanClose_clicked();

    void on_btnRelay1Open_clicked();

    void on_btnRelay1Close_clicked();

    void on_btnRelay2Open_clicked();

    void on_btnRelay2Close_clicked();

    void on_btnLockOpen_clicked();

    void on_btnLockClose_clicked();

    void on_btnColor_clicked();

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
